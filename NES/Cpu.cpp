/*----------------------------------------------------------------------*/
/*                                                                      */
/*      6502 CPU Core v0.00                                             */
/*                                                           Norix      */
/*                                               written     2000/12/23 */
/*                                               last modify ----/--/-- */
/*----------------------------------------------------------------------*/
/*--------------[ INCLUDE               ]-------------------------------*/
#include "VirtuaNESres.h"

#include "Base/Typedef.h"
#include "Base/Macro.h"

#include "Base/DebugOut.h"
#include "Base/AppWrapper.h"
#include "Base/ConfigWrapper.h"

#include "Nes.h"
#include "MMU.h"
#include "CPU.h"
#include "PPU.h"
#include "APU.h"
#include "ROM.h"
#include "Mapper/Mapper.h"
#include "CPUExecutor.hpp"

//
// コンストラクタ/デストラクタ
//
//CPU::CPU( NES* parent )
CPU::CPU(NES* parent, MMUClass &mmu) : nes(parent), mmu(mmu) {
	//	nes = parent;
	m_bClockProcess = FALSE;
}

CPU::~CPU() {
}

BYTE CPU::RD6502(WORD addr) {
	if (addr < 0x2000) {
		// RAM (Mirror $0800, $1000, $1800)
		return mmu.RAM[addr & 0x07FF];
	}
	if (addr < 0x8000) {
		// Others
		return nes->Read(addr);
	}
	// Dummy access
	mapper->Read(addr, mmu.CPU_MEM_BANK[addr >> 13][addr & 0x1FFF]);

	// Quick bank read
	return mmu.CPU_MEM_BANK[addr >> 13][addr & 0x1FFF];
}

WORD CPU::RD6502W(WORD addr) {
	if (addr < 0x2000) {
		// RAM (Mirror $0800, $1000, $1800)
		return *((WORD*)&mmu.RAM[addr & 0x07FF]);
	}
	if (addr < 0x8000) {
		// Others
		return static_cast<WORD>(nes->Read(addr)) + static_cast<WORD>(nes->Read(addr + 1)) * 0x100;
	}

	// Quick bank read
#if	0
	WORD	ret;
	ret  = (WORD)mmu.CPU_MEM_BANK[(addr+0)>>13][(addr+0)&0x1FFF];
	ret |= (WORD)mmu.CPU_MEM_BANK[(addr+1)>>13][(addr+1)&0x1FFF]<<8;
	return	ret;
#else
	return *((WORD*)&mmu.CPU_MEM_BANK[addr >> 13][addr & 0x1FFF]);
#endif
}

// メモリライト
void CPU::WR6502(WORD addr, BYTE data) {
	if (addr < 0x2000) {
		// RAM (Mirror $0800, $1000, $1800)
		mmu.RAM[addr & 0x07FF] = data;
	}
	else {
		// Others
		nes->Write(addr, data);
	}
}

//
// リセット
//
void CPU::Reset() {
	apu = nes->apu;
	mapper = nes->mapper;

	R.A = 0x00;
	R.X = 0x00;
	R.Y = 0x00;
	R.S = 0xFF;
	R.P = Z_FLAG | R_FLAG;
	R.PC = RD6502W(RES_VECTOR);

	R.INT_pending = 0;

	TOTAL_cycles = 0;
	DMA_cycles = 0;

	// STACK quick access
	STACK = &mmu.RAM[0x0100];

	// Zero/Negative FLAG
	ZN_Table[0] = Z_FLAG;
	for (INT i = 1; i < 256; i++)
		ZN_Table[i] = (i & 0x80) ? N_FLAG : 0;
}

INT CPU::GetDmaCycles() {
	return DMA_cycles;
}

void CPU::SetDmaCycles(INT cycles) {
	DMA_cycles = cycles;
}

INT CPU::GetTotalCycles() {
	return TOTAL_cycles;
}

void CPU::SetTotalCycles(INT cycles) {
	TOTAL_cycles = cycles;
}

//
// DMAペンディングサイクル設定
//
void CPU::DMA(INT cycles) {
	DMA_cycles += cycles;
}

static int nmicount;

//
// 割り込み
//
void CPU::NMI() {
	R.INT_pending |= NMI_FLAG;
	nmicount = 0;
}

void CPU::SetIRQ(BYTE mask) {
	R.INT_pending |= mask;
}

void CPU::ClrIRQ(BYTE mask) {
	R.INT_pending &= ~mask;
}

//
// 命令実行
//
INT CPU::EXEC(INT request_cycles) {
	return Executor(*this).Exec(request_cycles);
}

int CPU::Executor::Exec(int request_cycles) {
	while (request_cycles > 0) {
		exec_cycles = 0;

		if (DMA_cycles) {
			if (request_cycles <= DMA_cycles) {
				DMA_cycles -= request_cycles;
				TOTAL_cycles += request_cycles;

				// クロック同期処理
				mapper->Clock(request_cycles);
#if	DPCM_SYNCCLOCK
				apu->SyncDPCM( request_cycles );
#endif
				if (bClockProcess) {
					nes->Clock(request_cycles);
				}
				//				nes->Clock( request_cycles );
				goto _execute_exit;
			}
			exec_cycles += DMA_cycles;
			//				request_cycles -= DMA_cycles;
			DMA_cycles = 0;
		}

		nmi_request = irq_request = 0;
		const BYTE opcode = OP6502(R.PC++); // オペコード

		if (R.INT_pending) {
			if (R.INT_pending & NMI_FLAG) {
				nmi_request = 0xFF;
				R.INT_pending &= ~NMI_FLAG;
			}
			else if (R.INT_pending & IRQ_MASK) {
				R.INT_pending &= ~IRQ_TRIGGER2;
				if (!(R.P & I_FLAG) && opcode != 0x40) {
					irq_request = 0xFF;
					R.INT_pending &= ~IRQ_TRIGGER;
				}
			}
		}

		const bool succ = DoExec(opcode);
		if (!succ) {
			if (!ConfigWrapper::GetCCfgEmulator().bIllegalOp) {
				throw AppWrapper::GetErrorString(IDS_ERROR_ILLEGALOPCODE);
				goto _execute_exit;
			}
			R.PC--;
			ADD_CYCLE(4);
		}

		if (nmi_request) {
			_NMI();
		}
		else if (irq_request) {
			_IRQ();
		}

		request_cycles -= exec_cycles;
		TOTAL_cycles += exec_cycles;

		// クロック同期処理
		mapper->Clock(exec_cycles);
#if	DPCM_SYNCCLOCK
		apu->SyncDPCM( exec_cycles );
#endif
		if (bClockProcess) {
			nes->Clock(exec_cycles);
		}
		//		nes->Clock( exec_cycles );
	}
_execute_exit:

#if	!DPCM_SYNCCLOCK
	apu->SyncDPCM(TOTAL_cycles - OLD_cycles);
#endif

	return TOTAL_cycles - OLD_cycles;
}
