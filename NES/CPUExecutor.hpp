#pragma once
#include <initializer_list>
#include <array>


#include "CPU.h"
#include "MMU.h"
#include "NES.h"
#include "Base/Typedef.h"

class CPU::Executor
{
private:
	// Referencs from class CPU
	CPU& cpu;

	NES*& nes;
	APU*& apu;
	Mapper*& mapper;

	R6502& R;

	INT& TOTAL_cycles; // CPUトータルサイクル数
	INT& DMA_cycles; // DMAサイクル数

	// PTR
	LPBYTE& STACK;

	// Zero & Negative table
	BYTE(&ZN_Table)[256];

	// Clock process
	BOOL& m_bClockProcess;
	
	MMUClass& mmu;

	BYTE RD6502(WORD addr) {
		return cpu.RD6502(addr);
	}

	void WR6502(WORD addr, BYTE data) {
		return cpu.WR6502(addr, data);
	}

	WORD RD6502W(WORD addr) {
		return cpu.RD6502W(addr);
	}

private:
	INT OLD_cycles = TOTAL_cycles;
	INT exec_cycles = 0;
	BYTE nmi_request = 0, irq_request = 0;
	BOOL bClockProcess = m_bClockProcess;

	// TEMP
	WORD EA = 0;
	WORD ET = 0;
	WORD WT = 0;
	BYTE DT = 0;
public:
	// メモリアクセス
	//#define	OP6502(A)	(mmu.CPU_MEM_BANK[(A)>>13][(A)&0x1FFF])
	//#define	OP6502W(A)	(*((WORD*)&mmu.CPU_MEM_BANK[(A)>>13][(A)&0x1FFF]))

#if	0
#define	OP6502(A)	RD6502((A))
#define	OP6502W(A)	RD6502W((A))
#else
	BYTE OP6502(WORD addr) {
		return mmu.GetCPU_MEM_BANK(addr);
	}

	WORD OP6502W(WORD addr) {
#if	0
		WORD	ret;
		ret = (WORD)mmu.CPU_MEM_BANK[(addr + 0) >> 13][(addr + 0) & 0x1FFF];
		ret |= (WORD)mmu.CPU_MEM_BANK[(addr + 1) >> 13][(addr + 1) & 0x1FFF] << 8;
		return	ret;
#else
		return reinterpret_cast<WORD&>(mmu.GetCPU_MEM_BANK(addr));
#endif
	}
#endif

	int Exec(int request_cycles);
private:
	using ExecFunc = void (Executor::*) ();
public:
	struct OpCode {
		OpCode() = default;
		OpCode(const std::initializer_list<ExecFunc> &funcs, int cycle)
			: cycle(cycle) {
			size_t i = 0;
			for (auto f : funcs) {
				this->funcs[i++] = f;
			}
		}
		std::array<ExecFunc, 4> funcs = {};
		int cycle = 0;
	};
	using OpcodeDataType = std::array<OpCode, 0x100>;
private:
	bool DoExec(BYTE opcode);
public:
	Executor(CPU& cpu) :
		cpu(cpu),
		nes(cpu.nes),
		apu(cpu.apu),
		mapper(cpu.mapper),
		R(cpu.R),
		TOTAL_cycles(cpu.TOTAL_cycles),
		DMA_cycles(cpu.DMA_cycles),
		STACK(cpu.STACK),
		ZN_Table(cpu.ZN_Table),
		m_bClockProcess(cpu.m_bClockProcess),
		mmu(cpu.nes->mmu) {
	}

	/*--------------[ DEFINE                ]-------------------------------*/
#define	DPCM_SYNCCLOCK	FALSE
	/*--------------[ EXTERNAL PROGRAM      ]-------------------------------*/
	/*--------------[ EXTERNAL WORK         ]-------------------------------*/
	/*--------------[ WORK                  ]-------------------------------*/
	/*--------------[ CONST                 ]-------------------------------*/
	/*--------------[ PROTOTYPE             ]-------------------------------*/
	/*--------------[ PROGRAM               ]-------------------------------*/
	// オペコード
	//#define	OP6502(A)	RD6502((A))
	//#define	OP6502W(A)	RD6502W((A))

	// ゼロページリード
	template <typename T>
	auto ZPRD(T A) { return mmu.RAM[static_cast<BYTE>(A)]; }

	//template <typename T> auto ZPRDW(T A) { return *((LPWORD)&mmu.RAM[(BYTE)(A)]); }
	template <typename T>
	WORD ZPRDW(T A) {
		return static_cast<WORD>(mmu.RAM[static_cast<BYTE>(A)]) + (static_cast<WORD>(mmu.RAM[static_cast<BYTE>((A)+1)]
			) << 8);
	}

	template <typename T1, typename T2>
	auto ZPWR(T1 A, T2 V) { return mmu.RAM[static_cast<BYTE>(A)] = (V); }

	template <typename T1, typename T2>
	auto ZPWRW(T1 A, T2 V) { return *((LPWORD)&mmu.RAM[static_cast<BYTE>(A)]) = static_cast<WORD>(V); }

	// サイクルカウンタ
	auto ADD_CYCLE(int V) { exec_cycles += (V); }

	//template <typename T> auto	ADD_CYCLE(T V)	{}

	// EFFECTIVE ADDRESSページ境界超えチェック
	auto CHECK_EA() { if ((ET & 0xFF00) != (EA & 0xFF00)) ADD_CYCLE(1); }
	//auto	CHECK_EA()	{ if( (R.PC&0xFF00) != (EA&0xFF00) ) ADD_CYCLE(1); }
	//auto	CHECK_EA()	{}

	// フラグ操作
	// ゼロ／ネガティブフラグのチェックと設定
	template <typename T>
	void SET_ZN_FLAG(T A) {
		R.P &= ~(Z_FLAG | N_FLAG);
		R.P |= ZN_Table[static_cast<BYTE>(A)];
	}

	// フラグセット
	template <typename T>
	void SET_FLAG(T V) { R.P |= (V); }

	// フラグクリア
	template <typename T>
	void CLR_FLAG(T V) { R.P &= ~(V); }

	// フラグテスト＆セット／クリア
	template <typename T1, typename T2>
	void TST_FLAG(T1 F, T2 V) {
		R.P &= ~(V);
		if ((F)) R.P |= (V);
	}

	// フラグチェック
	template <typename T>
	auto CHK_FLAG(T V) { return R.P & (V); }

	// WT .... WORD TEMP
	// EA .... EFFECTIVE ADDRESS
	// ET .... EFFECTIVE ADDRESS TEMP
	// DT .... DATA

	void MR_IM() {
		DT = OP6502(R.PC++);
	}

	void MR_ZP() {
		EA = OP6502(R.PC++);
		DT = ZPRD(EA);
	}

	void MR_ZX() {
		DT = OP6502(R.PC++);
		EA = static_cast<BYTE>(DT + R.X);
		DT = ZPRD(EA);
	}

	void MR_ZY() {
		DT = OP6502(R.PC++);
		EA = static_cast<BYTE>(DT + R.Y);
		DT = ZPRD(EA);
	}

	void MR_AB() {
		EA = OP6502W(R.PC);
		R.PC += 2;
		DT = RD6502(EA);
	}

	void MR_AX() {
		ET = OP6502W(R.PC);
		R.PC += 2;
		EA = ET + R.X;
		DT = RD6502(EA);
	}

	void MR_AY() {
		ET = OP6502W(R.PC);
		R.PC += 2;
		EA = ET + R.Y;
		DT = RD6502(EA);
	}

	void MR_IX() {
		DT = OP6502(R.PC++);
		EA = ZPRDW(DT + R.X);
		DT = RD6502(EA);
	}

	void MR_IY() {
		DT = OP6502(R.PC++);
		ET = ZPRDW(DT);
		EA = ET + R.Y;
		DT = RD6502(EA);
	}

	// EFFECTIVE ADDRESS
	void EA_ZP() {
		EA = OP6502(R.PC++);
	}

	void EA_ZX() {
		DT = OP6502(R.PC++);
		EA = static_cast<BYTE>(DT + R.X);
	}

	void EA_ZY() {
		DT = OP6502(R.PC++);
		EA = static_cast<BYTE>(DT + R.Y);
	}

	void EA_AB() {
		EA = OP6502W(R.PC);
		R.PC += 2;
	}

	void EA_AX() {
		ET = OP6502W(R.PC);
		R.PC += 2;
		EA = ET + R.X;
	}

	void EA_AY() {
		ET = OP6502W(R.PC);
		R.PC += 2;
		EA = ET + R.Y;
	}

	void EA_IX() {
		DT = OP6502(R.PC++);
		EA = ZPRDW(DT + R.X);
	}

	void EA_IY() {
		DT = OP6502(R.PC++);
		ET = ZPRDW(DT);
		EA = ET + static_cast<WORD>(R.Y);
	}

	// メモリライト
	void MW_ZP() { ZPWR(EA, DT); }
	void MW_EA() { WR6502(EA, DT); }

	// STACK操作
	template <typename T>
	void PUSH(T V) { STACK[(R.S--) & 0xFF] = (V); }

	auto POP() { return STACK[(++R.S) & 0xFF]; }

	// 算術演算系
	/* ADC (NV----ZC) */
	void ADC() {
		WT = R.A + DT + (R.P & C_FLAG);
		TST_FLAG(WT > 0xFF, C_FLAG);
		TST_FLAG(((~(R.A ^ DT)) & (R.A ^ WT) & 0x80), V_FLAG);
		R.A = static_cast<BYTE>(WT);
		SET_ZN_FLAG(R.A);
	}

	/* SBC (NV----ZC) */
	void SBC() {
		WT = R.A - DT - (~R.P & C_FLAG);
		TST_FLAG(((R.A ^ DT) & (R.A ^ WT) & 0x80), V_FLAG);
		TST_FLAG(WT < 0x100, C_FLAG);
		R.A = static_cast<BYTE>(WT);
		SET_ZN_FLAG(R.A);
	}

	/* INC (N-----Z-) */
	void INC() {
		DT++;
		SET_ZN_FLAG(DT);
	}

	/* INX (N-----Z-) */
	void INX() {
		R.X++;
		SET_ZN_FLAG(R.X);
	}

	/* INY (N-----Z-) */
	void INY() {
		R.Y++;
		SET_ZN_FLAG(R.Y);
	}

	/* DEC (N-----Z-) */
	void DEC() {
		DT--;
		SET_ZN_FLAG(DT);
	}

	/* DEX (N-----Z-) */
	void DEX() {
		R.X--;
		SET_ZN_FLAG(R.X);
	}

	/* DEY (N-----Z-) */
	void DEY() {
		R.Y--;
		SET_ZN_FLAG(R.Y);
	}

	// 論理演算系
	/* AND (N-----Z-) */
	void AND() {
		R.A &= DT;
		SET_ZN_FLAG(R.A);
	}

	/* ORA (N-----Z-) */
	void ORA() {
		R.A |= DT;
		SET_ZN_FLAG(R.A);
	}

	/* EOR (N-----Z-) */
	void EOR() {
		R.A ^= DT;
		SET_ZN_FLAG(R.A);
	}

	/* ASL_A (N-----ZC) */
	void ASL_A() {
		TST_FLAG(R.A & 0x80, C_FLAG);
		R.A <<= 1;
		SET_ZN_FLAG(R.A);
	}

	/* ASL (N-----ZC) */
	void ASL() {
		TST_FLAG(DT & 0x80, C_FLAG);
		DT <<= 1;
		SET_ZN_FLAG(DT);
	}

	/* LSR_A (N-----ZC) */
	void LSR_A() {
		TST_FLAG(R.A & 0x01, C_FLAG);
		R.A >>= 1;
		SET_ZN_FLAG(R.A);
	}

	/* LSR (N-----ZC) */
	void LSR() {
		TST_FLAG(DT & 0x01, C_FLAG);
		DT >>= 1;
		SET_ZN_FLAG(DT);
	}

	/* ROL_A (N-----ZC) */
	void ROL_A() {
		if (R.P & C_FLAG) {
			TST_FLAG(R.A & 0x80, C_FLAG);
			R.A = (R.A << 1) | 0x01;
		}
		else {
			TST_FLAG(R.A & 0x80, C_FLAG);
			R.A <<= 1;
		}
		SET_ZN_FLAG(R.A);
	}

	/* ROL (N-----ZC) */
	void ROL() {
		if (R.P & C_FLAG) {
			TST_FLAG(DT & 0x80, C_FLAG);
			DT = (DT << 1) | 0x01;
		}
		else {
			TST_FLAG(DT & 0x80, C_FLAG);
			DT <<= 1;
		}
		SET_ZN_FLAG(DT);
	}

	/* ROR_A (N-----ZC) */
	void ROR_A() {
		if (R.P & C_FLAG) {
			TST_FLAG(R.A & 0x01, C_FLAG);
			R.A = (R.A >> 1) | 0x80;
		}
		else {
			TST_FLAG(R.A & 0x01, C_FLAG);
			R.A >>= 1;
		}
		SET_ZN_FLAG(R.A);
	}

	/* ROR (N-----ZC) */
	void ROR() {
		if (R.P & C_FLAG) {
			TST_FLAG(DT & 0x01, C_FLAG);
			DT = (DT >> 1) | 0x80;
		}
		else {
			TST_FLAG(DT & 0x01, C_FLAG);
			DT >>= 1;
		}
		SET_ZN_FLAG(DT);
	}

	/* BIT (NV----Z-) */
	void BIT() {
		TST_FLAG((DT & R.A) == 0, Z_FLAG);
		TST_FLAG(DT & 0x80, N_FLAG);
		TST_FLAG(DT & 0x40, V_FLAG);
	}

	// ロード／ストア系
	/* LDA (N-----Z-) */
	void LDA() {
		R.A = DT;
		SET_ZN_FLAG(R.A);
	}

	/* LDX (N-----Z-) */
	void LDX() {
		R.X = DT;
		SET_ZN_FLAG(R.X);
	}

	/* LDY (N-----Z-) */
	void LDY() {
		R.Y = DT;
		SET_ZN_FLAG(R.Y);
	}

	/* STA (--------) */
	void STA() { DT = R.A; }
	/* STX (--------) */
	void STX() { DT = R.X; }
	/* STY (--------) */
	void STY() { DT = R.Y; }

	/* TAX (N-----Z-) */
	void TAX() {
		R.X = R.A;
		SET_ZN_FLAG(R.X);
	}

	/* TXA (N-----Z-) */
	void TXA() {
		R.A = R.X;
		SET_ZN_FLAG(R.A);
	}

	/* TAY (N-----Z-) */
	void TAY() {
		R.Y = R.A;
		SET_ZN_FLAG(R.Y);
	}

	/* TYA (N-----Z-) */
	void TYA() {
		R.A = R.Y;
		SET_ZN_FLAG(R.A);
	}

	/* TSX (N-----Z-) */
	void TSX() {
		R.X = R.S;
		SET_ZN_FLAG(R.X);
	}

	/* TXS (--------) */
	void TXS() { R.S = R.X; }

	// 比較系
	/* CMP (N-----ZC) */
	void CMP_() {
		WT = static_cast<WORD>(R.A) - static_cast<WORD>(DT);
		TST_FLAG((WT & 0x8000) == 0, C_FLAG);
		SET_ZN_FLAG(static_cast<BYTE>(WT));
	}

	/* CPX (N-----ZC) */
	void CPX() {
		WT = static_cast<WORD>(R.X) - static_cast<WORD>(DT);
		TST_FLAG((WT & 0x8000) == 0, C_FLAG);
		SET_ZN_FLAG(static_cast<BYTE>(WT));
	}

	/* CPY (N-----ZC) */
	void CPY() {
		WT = static_cast<WORD>(R.Y) - static_cast<WORD>(DT);
		TST_FLAG((WT & 0x8000) == 0, C_FLAG);
		SET_ZN_FLAG(static_cast<BYTE>(WT));
	}

	// ジャンプ／リターン系
#if	1
	void JMP_ID() {
		WT = OP6502W(R.PC);
		EA = RD6502(WT);
		WT = (WT & 0xFF00) | ((WT + 1) & 0x00FF);
		R.PC = EA + RD6502(WT) * 0x100;
	}
#else
	void	JMP_ID() {
		\
			ET = OP6502W(R.PC);	\
			EA = RD6502W(ET);	\
			R.PC = EA;		\
	}
#endif
	void JMP() {
		R.PC = OP6502W(R.PC);
	}

	void JSR() {
		EA = OP6502W(R.PC);
		R.PC++;
		PUSH(R.PC >> 8);
		PUSH(R.PC & 0xFF);
		R.PC = EA;
	}

	void RTS() {
		R.PC = POP();
		R.PC |= POP() * 0x0100;
		R.PC++;
	}

	void RTI() {
		R.P = POP() | R_FLAG;
		R.PC = POP();
		R.PC |= POP() * 0x0100;
	}

	void _NMI() {
		PUSH(R.PC >> 8);
		PUSH(R.PC & 0xFF);
		CLR_FLAG(B_FLAG);
		PUSH(R.P);
		SET_FLAG(I_FLAG);
		R.PC = RD6502W(NMI_VECTOR);
		exec_cycles += 7;
	}

	void _IRQ() {
		PUSH(R.PC >> 8);
		PUSH(R.PC & 0xFF);
		CLR_FLAG(B_FLAG);
		PUSH(R.P);
		SET_FLAG(I_FLAG);
		R.PC = RD6502W(IRQ_VECTOR);
		exec_cycles += 7;
	}

	void BRK() {
		R.PC++;
		PUSH(R.PC >> 8);
		PUSH(R.PC & 0xFF);
		SET_FLAG(B_FLAG);
		PUSH(R.P);
		SET_FLAG(I_FLAG);
		R.PC = RD6502W(IRQ_VECTOR);
	}

#if	1
	void REL_JUMP() {
		ET = R.PC;
		EA = R.PC + static_cast<SBYTE>(DT);
		R.PC = EA;
		ADD_CYCLE(1);
		CHECK_EA();
	}
#else
	void	REL_JUMP() {
		\
			R.PC = R.PC + (SBYTE)DT;	\
			ADD_CYCLE(1);			\
	}
#endif

	void BCC() { if (!(R.P & C_FLAG)) REL_JUMP(); }
	void BCS() { if ((R.P & C_FLAG)) REL_JUMP(); }
	void BNE() { if (!(R.P & Z_FLAG)) REL_JUMP(); }
	void BEQ() { if ((R.P & Z_FLAG)) REL_JUMP(); }
	void BPL() { if (!(R.P & N_FLAG)) REL_JUMP(); }
	void BMI() { if ((R.P & N_FLAG)) REL_JUMP(); }
	void BVC() { if (!(R.P & V_FLAG)) REL_JUMP(); }
	void BVS() { if ((R.P & V_FLAG)) REL_JUMP(); }

	// フラグ制御系
	void CLC() { R.P &= ~C_FLAG; }
	void CLD() { R.P &= ~D_FLAG; }
	void CLI() { R.P &= ~I_FLAG; }
	void CLV() { R.P &= ~V_FLAG; }
	void SEC() { R.P |= C_FLAG; }
	void SED() { R.P |= D_FLAG; }
	void SEI() { R.P |= I_FLAG; }

	void PHA() { PUSH(R.A); }
	void PHP() { PUSH(R.P | B_FLAG); }
	void PLA() {
		R.A = POP();
		SET_ZN_FLAG(R.A);
	}
	void PLP() {
		R.P = POP() | R_FLAG;
	}

	// Unofficial命令
	void ANC() {
		R.A &= DT;
		SET_ZN_FLAG(R.A);
		TST_FLAG(R.P & N_FLAG, C_FLAG);
	}

	void ANE() {
		R.A = (R.A | 0xEE) & R.X & DT;
		SET_ZN_FLAG(R.A);
	}

	void ARR() {
		DT &= R.A;
		R.A = (DT >> 1) | ((R.P & C_FLAG) << 7);
		SET_ZN_FLAG(R.A);
		TST_FLAG(R.A & 0x40, C_FLAG);
		TST_FLAG((R.A >> 6) ^ (R.A >> 5), V_FLAG);
	}

	void ASR() {
		DT &= R.A;
		TST_FLAG(DT & 0x01, C_FLAG);
		R.A = DT >> 1;
		SET_ZN_FLAG(R.A);
	}

	void DCP() {
		DT--;
		CMP_();
	}

	void DOP() {
		R.PC++;
	}

	void ISB() {
		DT++;
		SBC();
	}

	void LAS() {
		R.A = R.X = R.S = (R.S & DT);
		SET_ZN_FLAG(R.A);
	}

	void LAX() {
		R.A = DT;
		R.X = R.A;
		SET_ZN_FLAG(R.A);
	}

	void LXA() {
		R.A = R.X = ((R.A | 0xEE) & DT);
		SET_ZN_FLAG(R.A);
	}

	void RLA() {
		if (R.P & C_FLAG) {
			TST_FLAG(DT & 0x80, C_FLAG);
			DT = (DT << 1) | 1;
		}
		else {
			TST_FLAG(DT & 0x80, C_FLAG);
			DT <<= 1;
		}
		R.A &= DT;
		SET_ZN_FLAG(R.A);
	}

	void RRA() {
		if (R.P & C_FLAG) {
			TST_FLAG(DT & 0x01, C_FLAG);
			DT = (DT >> 1) | 0x80;
		}
		else {
			TST_FLAG(DT & 0x01, C_FLAG);
			DT >>= 1;
		}
		ADC();
	}

	void SAX() {
		DT = R.A & R.X;
	}

	void SBX() {
		WT = (R.A & R.X) - DT;
		TST_FLAG(WT < 0x100, C_FLAG);
		R.X = WT & 0xFF;
		SET_ZN_FLAG(R.X);
	}

	void SHA() {
		DT = R.A & R.X & static_cast<BYTE>((EA >> 8) + 1);
	}

	void SHS() {
		R.S = R.A & R.X;
		DT = R.S & static_cast<BYTE>((EA >> 8) + 1);
	}

	void SHX() {
		DT = R.X & static_cast<BYTE>((EA >> 8) + 1);
	}

	void SHY() {
		DT = R.Y & static_cast<BYTE>((EA >> 8) + 1);
	}

	void SLO() {
		TST_FLAG(DT & 0x80, C_FLAG);
		DT <<= 1;
		R.A |= DT;
		SET_ZN_FLAG(R.A);
	}

	void SRE() {
		TST_FLAG(DT & 0x01, C_FLAG);
		DT >>= 1;
		R.A ^= DT;
		SET_ZN_FLAG(R.A);
	}

	void TOP() {
		R.PC += 2;
	}
};
