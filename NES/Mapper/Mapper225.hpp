//////////////////////////////////////////////////////////////////////////
// Mapper225  72-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper225::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, 2, 3 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper225::Write( WORD addr, BYTE data )
{
	BYTE prg_bank = (addr & 0x0F80) >> 7;
	BYTE chr_bank = addr & 0x003F;

	nes->mmu.SetVROM_1K_Bank(0,(chr_bank*8+0));
	nes->mmu.SetVROM_1K_Bank(1,(chr_bank*8+1));
	nes->mmu.SetVROM_1K_Bank(2,(chr_bank*8+2));
	nes->mmu.SetVROM_1K_Bank(3,(chr_bank*8+3));
	nes->mmu.SetVROM_1K_Bank(4,(chr_bank*8+4));
	nes->mmu.SetVROM_1K_Bank(5,(chr_bank*8+5));
	nes->mmu.SetVROM_1K_Bank(6,(chr_bank*8+6));
	nes->mmu.SetVROM_1K_Bank(7,(chr_bank*8+7));

	if( addr & 0x2000 ) {
		nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
	}

	if( addr & 0x1000 ) {
		// 16KBbank
		if( addr & 0x0040 ) {
			nes->mmu.SetPROM_8K_Bank(4,(prg_bank*4+2));
			nes->mmu.SetPROM_8K_Bank(5,(prg_bank*4+3));
			nes->mmu.SetPROM_8K_Bank(6,(prg_bank*4+2));
			nes->mmu.SetPROM_8K_Bank(7,(prg_bank*4+3));
		} else {
			nes->mmu.SetPROM_8K_Bank(4,(prg_bank*4+0));
			nes->mmu.SetPROM_8K_Bank(5,(prg_bank*4+1));
			nes->mmu.SetPROM_8K_Bank(6,(prg_bank*4+0));
			nes->mmu.SetPROM_8K_Bank(7,(prg_bank*4+1));
		}
	} else {
		nes->mmu.SetPROM_8K_Bank(4,(prg_bank*4+0));
		nes->mmu.SetPROM_8K_Bank(5,(prg_bank*4+1));
		nes->mmu.SetPROM_8K_Bank(6,(prg_bank*4+2));
		nes->mmu.SetPROM_8K_Bank(7,(prg_bank*4+3));
	}
}
