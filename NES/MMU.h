//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      NES Memory Management Unit                                      //
//                                                           Norix      //
//                                               written     2001/02/21 //
//                                               last modify ----/--/-- //
//////////////////////////////////////////////////////////////////////////

#ifndef	__MMU_INCLUDED__
#define	__MMU_INCLUDED__

#include "Base/Typedef.h"

struct MMUClass
{
	// CPU メモリバンク
	LPBYTE	CPU_MEM_BANK[8];	// 8K単位
	BYTE	CPU_MEM_TYPE[8];
	INT	CPU_MEM_PAGE[8];		// ステートセーブ用

	// PPU メモリバンク
	LPBYTE	PPU_MEM_BANK[12];	// 1K単位
	BYTE	PPU_MEM_TYPE[12];
	INT	PPU_MEM_PAGE[12];		// ステートセーブ用
	BYTE	CRAM_USED[16];		// ステートセーブ用

	// NESメモリ
	BYTE	RAM [  8*1024];		// NES内臓RAM
	BYTE	WRAM[128*1024];		// ワーク/バックアップRAM
	BYTE	DRAM[ 40*1024];		// ディスクシステムRAM
	BYTE	XRAM[  8*1024];		// ダミーバンク
	BYTE	ERAM[ 32*1024];		// 拡張機器用RAM

	BYTE	CRAM[ 32*1024];		// キャラクタパターンRAM
	BYTE	VRAM[  4*1024];		// ネームテーブル/アトリビュートRAM

	BYTE	SPRAM[0x100];		// スプライトRAM
	BYTE	BGPAL[0x10];		// BGパレット
	BYTE	SPPAL[0x10];		// SPパレット

	// レジスタ
	BYTE	CPUREG[0x18];		// Nes $4000-$4017
	BYTE	PPUREG[0x04];		// Nes $2000-$2003

	// Frame-IRQレジスタ($4017)
	BYTE	FrameIRQ;

	// PPU内部レジスタ
	BYTE	PPU56Toggle;		// $2005-$2006 Toggle
	BYTE	PPU7_Temp;			// $2007 read buffer
	WORD	loopy_t;			// same as $2005/$2006
	WORD	loopy_v;			// same as $2005/$2006
	WORD	loopy_x;			// tile x offset

	// ROMデータポインタ
	LPBYTE	PROM;		// PROM ptr
	LPBYTE	VROM;		// VROM ptr

#ifdef	_DATATRACE
// For dis...
	LPBYTE	PROM_ACCESS = NULL;
#endif

	// ROM バンクサイズ
	INT	PROM_8K_SIZE, PROM_16K_SIZE, PROM_32K_SIZE;
	INT	VROM_1K_SIZE, VROM_2K_SIZE, VROM_4K_SIZE, VROM_8K_SIZE;


	// 関数
	void	NesSub_MemoryInitial();

	void	SetPROM_Bank(BYTE page, LPBYTE ptr, BYTE type);
	void	SetPROM_8K_Bank(BYTE page, INT bank);
	void	SetPROM_16K_Bank(BYTE page, INT bank);
	void	SetPROM_32K_Bank(INT bank);
	void	SetPROM_32K_Bank(INT bank0, INT bank1, INT bank2, INT bank3);

	void	SetVROM_Bank(BYTE page, LPBYTE ptr, BYTE type);
	void	SetVROM_1K_Bank(BYTE page, INT bank);
	void	SetVROM_2K_Bank(BYTE page, INT bank);
	void	SetVROM_4K_Bank(BYTE page, INT bank);
	void	SetVROM_8K_Bank(INT bank);
	void	SetVROM_8K_Bank(INT bank0, INT bank1, INT bank2, INT bank3,
		INT bank4, INT bank5, INT bank6, INT bank7);

	void	SetCRAM_1K_Bank(BYTE page, INT bank);
	void	SetCRAM_2K_Bank(BYTE page, INT bank);
	void	SetCRAM_4K_Bank(BYTE page, INT bank);
	void	SetCRAM_8K_Bank(INT bank);

	void	SetVRAM_1K_Bank(BYTE page, INT bank);
	void	SetVRAM_Bank(INT bank0, INT bank1, INT bank2, INT bank3);
	void	SetVRAM_Mirror(INT type);
	void	SetVRAM_Mirror(INT bank0, INT bank1, INT bank2, INT bank3);

	auto&	GetCPU_MEM_BANK(WORD addr) {
		return CPU_MEM_BANK[addr >> 13][addr & 0x1FFF];
	}
	auto&	GetRAM(WORD addr) {
		return RAM[addr & 0x07FF];
	}
};

extern MMUClass GlobalMMU;

// メモリタイプ
// For PROM (CPU)
#define	BANKTYPE_ROM	0x00
#define	BANKTYPE_RAM	0xFF
#define	BANKTYPE_DRAM	0x01
#define	BANKTYPE_MAPPER	0x80
// For VROM/VRAM/CRAM (PPU)
#define	BANKTYPE_VROM	0x00
#define	BANKTYPE_CRAM	0x01
#define	BANKTYPE_VRAM	0x80

// ミラータイプ
#define	VRAM_HMIRROR	0x00	// Horizontal
#define	VRAM_VMIRROR	0x01	// Virtical
#define	VRAM_MIRROR4	0x02	// All screen
#define	VRAM_MIRROR4L	0x03	// PA10 L固定 $2000-$23FFのミラー
#define	VRAM_MIRROR4H	0x04	// PA10 H固定 $2400-$27FFのミラー

#endif	// !__MMU_INCLUDED__

