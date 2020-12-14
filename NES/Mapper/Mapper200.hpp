//////////////////////////////////////////////////////////////////////////
// Mapper200  1200-in-1                                                 //
//////////////////////////////////////////////////////////////////////////
void	Mapper200::Reset()
{
//	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	MMU.SetPROM_16K_Bank( 4, 0 );
	MMU.SetPROM_16K_Bank( 6, 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper200::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_16K_Bank( 4, addr & 0x07 );
	MMU.SetPROM_16K_Bank( 6, addr & 0x07 );
	MMU.SetVROM_8K_Bank( addr & 0x07 );

	if( addr & 0x01 ) {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	}
}
