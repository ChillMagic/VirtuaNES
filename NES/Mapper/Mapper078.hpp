//////////////////////////////////////////////////////////////////////////
// Mapper078  Jaleco(Cosmo Carrier)                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper078::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper078::Write( WORD addr, BYTE data )
{
//DEBUGOUT( "MAP78 WR $%04X=$%02X L=%d\n", addr, data, nes->GetScanline() );
	nes->mmu.SetPROM_16K_Bank( 4, data&0x0F );
	nes->mmu.SetVROM_8K_Bank( (data&0xF0)>>4 );

	if( (addr & 0xFE00) != 0xFE00 ) {
		if( data & 0x08 ) nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4H );
		else		  nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4L );
	}
}
