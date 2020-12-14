//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      NES Memory Management Unit                                      //
//                                                           Norix      //
//                                               written     2001/02/21 //
//                                               last modify ----/--/-- //
//////////////////////////////////////////////////////////////////////////
#include "Base/Typedef.h"
#include "Base/Macro.h"
#include "Base/DebugOut.h"

#include "MMU.h"

//
// 全メモリ/レジスタ等の初期化
//
void	MMUClass::NesSub_MemoryInitial()
{
INT	i;

	// メモリクリア
	ZEROMEMORY( RAM,  sizeof(RAM) );
	ZEROMEMORY( WRAM, sizeof(WRAM) );
	ZEROMEMORY( DRAM, sizeof(DRAM) );
	ZEROMEMORY( ERAM, sizeof(ERAM) );
	ZEROMEMORY( XRAM, sizeof(XRAM) );
	ZEROMEMORY( CRAM, sizeof(CRAM) );
	ZEROMEMORY( VRAM, sizeof(VRAM) );

	ZEROMEMORY( SPRAM, sizeof(SPRAM) );
	ZEROMEMORY( BGPAL, sizeof(BGPAL) );
	ZEROMEMORY( SPPAL, sizeof(SPPAL) );

	ZEROMEMORY( CPUREG, sizeof(CPUREG) );
	ZEROMEMORY( PPUREG, sizeof(PPUREG) );

	FrameIRQ = 0xC0;

	PROM = VROM = NULL;

	// 0 除算防止対策
	PROM_8K_SIZE = PROM_16K_SIZE = PROM_32K_SIZE = 1;
	VROM_1K_SIZE = VROM_2K_SIZE = VROM_4K_SIZE = VROM_8K_SIZE = 1;

	// デフォルトバンク設定
	for( i = 0; i < 8; i++ ) {
		CPU_MEM_BANK[i] = NULL;
		CPU_MEM_TYPE[i] = BANKTYPE_ROM;
		CPU_MEM_PAGE[i] = 0;
	}

	// 内臓RAM/WRAM
	SetPROM_Bank( 0, RAM,  BANKTYPE_RAM );
	SetPROM_Bank( 3, WRAM, BANKTYPE_RAM );

	// ダミー
	SetPROM_Bank( 1, XRAM, BANKTYPE_ROM );
	SetPROM_Bank( 2, XRAM, BANKTYPE_ROM );

	for( i = 0; i < 8; i++ ) {
		CRAM_USED[i] = 0;
	}

	// PPU VROMバンク設定
//	SetVRAM_Mirror( VRAM_MIRROR4 );
}

// CPU ROM bank
void	MMUClass::SetPROM_Bank( BYTE page, LPBYTE ptr, BYTE type )
{
	CPU_MEM_BANK[page] = ptr;
	CPU_MEM_TYPE[page] = type;
	CPU_MEM_PAGE[page] = 0;
}

void	MMUClass::SetPROM_8K_Bank( BYTE page, INT bank )
{
	bank %= PROM_8K_SIZE;
	CPU_MEM_BANK[page] = PROM+0x2000*bank;
	CPU_MEM_TYPE[page] = BANKTYPE_ROM;
	CPU_MEM_PAGE[page] = bank;
}

void	MMUClass::SetPROM_16K_Bank( BYTE page, INT bank )
{
	SetPROM_8K_Bank( page+0, bank*2+0 );
	SetPROM_8K_Bank( page+1, bank*2+1 );
}

void	MMUClass::SetPROM_32K_Bank( INT bank )
{
	SetPROM_8K_Bank( 4, bank*4+0 );
	SetPROM_8K_Bank( 5, bank*4+1 );
	SetPROM_8K_Bank( 6, bank*4+2 );
	SetPROM_8K_Bank( 7, bank*4+3 );
}

void	MMUClass::SetPROM_32K_Bank( INT bank0, INT bank1, INT bank2, INT bank3 )
{
	SetPROM_8K_Bank( 4, bank0 );
	SetPROM_8K_Bank( 5, bank1 );
	SetPROM_8K_Bank( 6, bank2 );
	SetPROM_8K_Bank( 7, bank3 );
}

// PPU VROM bank
void	MMUClass::SetVROM_Bank( BYTE page, LPBYTE ptr, BYTE type )
{
	PPU_MEM_BANK[page] = ptr;
	PPU_MEM_TYPE[page] = type;
	PPU_MEM_PAGE[page] = 0;
}

void	MMUClass::SetVROM_1K_Bank( BYTE page, INT bank )
{
	bank %= VROM_1K_SIZE;
	PPU_MEM_BANK[page] = VROM+0x0400*bank;
	PPU_MEM_TYPE[page] = BANKTYPE_VROM;
	PPU_MEM_PAGE[page] = bank;
}

void	MMUClass::SetVROM_2K_Bank( BYTE page, INT bank )
{
	SetVROM_1K_Bank( page+0, bank*2+0 );
	SetVROM_1K_Bank( page+1, bank*2+1 );
}

void	MMUClass::SetVROM_4K_Bank( BYTE page, INT bank )
{
	SetVROM_1K_Bank( page+0, bank*4+0 );
	SetVROM_1K_Bank( page+1, bank*4+1 );
	SetVROM_1K_Bank( page+2, bank*4+2 );
	SetVROM_1K_Bank( page+3, bank*4+3 );
}

void	MMUClass::SetVROM_8K_Bank( INT bank )
{
	for( INT i = 0; i < 8; i++ ) {
		SetVROM_1K_Bank( i, bank*8+i );
	}
}

void	MMUClass::SetVROM_8K_Bank( INT bank0, INT bank1, INT bank2, INT bank3,
			 INT bank4, INT bank5, INT bank6, INT bank7 )
{
	SetVROM_1K_Bank( 0, bank0 );
	SetVROM_1K_Bank( 1, bank1 );
	SetVROM_1K_Bank( 2, bank2 );
	SetVROM_1K_Bank( 3, bank3 );
	SetVROM_1K_Bank( 4, bank4 );
	SetVROM_1K_Bank( 5, bank5 );
	SetVROM_1K_Bank( 6, bank6 );
	SetVROM_1K_Bank( 7, bank7 );
}

void	MMUClass::SetCRAM_1K_Bank( BYTE page, INT bank )
{
	bank &= 0x1F;
	PPU_MEM_BANK[page] = CRAM+0x0400*bank;
	PPU_MEM_TYPE[page] = BANKTYPE_CRAM;
	PPU_MEM_PAGE[page] = bank;

	CRAM_USED[bank>>2] = 0xFF;	// CRAM使用フラグ
}

void	MMUClass::SetCRAM_2K_Bank( BYTE page, INT bank )
{
	SetCRAM_1K_Bank( page+0, bank*2+0 );
	SetCRAM_1K_Bank( page+1, bank*2+1 );
}

void	MMUClass::SetCRAM_4K_Bank( BYTE page, INT bank )
{
	SetCRAM_1K_Bank( page+0, bank*4+0 );
	SetCRAM_1K_Bank( page+1, bank*4+1 );
	SetCRAM_1K_Bank( page+2, bank*4+2 );
	SetCRAM_1K_Bank( page+3, bank*4+3 );
}

void	MMUClass::SetCRAM_8K_Bank( INT bank )
{
	for( INT i = 0; i < 8; i++ ) {
		SetCRAM_1K_Bank( i, bank*8+i );	// fix
	}
}

void	MMUClass::SetVRAM_1K_Bank( BYTE page, INT bank )
{
	bank &= 3;
	PPU_MEM_BANK[page] = VRAM+0x0400*bank;
	PPU_MEM_TYPE[page] = BANKTYPE_VRAM;
	PPU_MEM_PAGE[page] = bank;
}

void	MMUClass::SetVRAM_Bank( INT bank0, INT bank1, INT bank2, INT bank3 )
{
	SetVRAM_1K_Bank(  8, bank0 );
	SetVRAM_1K_Bank(  9, bank1 );
	SetVRAM_1K_Bank( 10, bank2 );
	SetVRAM_1K_Bank( 11, bank3 );
}

void	MMUClass::SetVRAM_Mirror( INT type )
{
	switch( type ) {
		case	VRAM_HMIRROR:
			SetVRAM_Bank( 0, 0, 1, 1 );
			break;
		case	VRAM_VMIRROR:
			SetVRAM_Bank( 0, 1, 0, 1 );
			break;
		case	VRAM_MIRROR4L:
			SetVRAM_Bank( 0, 0, 0, 0 );
			break;
		case	VRAM_MIRROR4H:
			SetVRAM_Bank( 1, 1, 1, 1 );
			break;
		case	VRAM_MIRROR4:
			SetVRAM_Bank( 0, 1, 2, 3 );
			break;
	}
}

void	MMUClass::SetVRAM_Mirror( INT bank0, INT bank1, INT bank2, INT bank3 )
{
	SetVRAM_1K_Bank(  8, bank0 );
	SetVRAM_1K_Bank(  9, bank1 );
	SetVRAM_1K_Bank( 10, bank2 );
	SetVRAM_1K_Bank( 11, bank3 );
}

MMUClass MMU;
