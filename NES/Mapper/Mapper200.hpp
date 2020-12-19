//////////////////////////////////////////////////////////////////////////
// Mapper200  1200-in-1                                                 //
//////////////////////////////////////////////////////////////////////////
void	Mapper200::Reset()
{
//	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetPROM_16K_Bank( 4, 0 );
	nes->mmu.SetPROM_16K_Bank( 6, 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper200::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_16K_Bank( 4, addr & 0x07 );
	nes->mmu.SetPROM_16K_Bank( 6, addr & 0x07 );
	nes->mmu.SetVROM_8K_Bank( addr & 0x07 );

	if( addr & 0x01 ) {
		nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
	} else {
		nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
	}
}
