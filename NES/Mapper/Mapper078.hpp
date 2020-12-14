//////////////////////////////////////////////////////////////////////////
// Mapper078  Jaleco(Cosmo Carrier)                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper078::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

	if( MMU.VROM_8K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper078::Write( WORD addr, BYTE data )
{
//DEBUGOUT( "MAP78 WR $%04X=$%02X L=%d\n", addr, data, nes->GetScanline() );
	MMU.SetPROM_16K_Bank( 4, data&0x0F );
	MMU.SetVROM_8K_Bank( (data&0xF0)>>4 );

	if( (addr & 0xFE00) != 0xFE00 ) {
		if( data & 0x08 ) MMU.SetVRAM_Mirror( VRAM_MIRROR4H );
		else		  MMU.SetVRAM_Mirror( VRAM_MIRROR4L );
	}
}
