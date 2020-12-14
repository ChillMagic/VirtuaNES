//////////////////////////////////////////////////////////////////////////
// Mapper011  Color Dreams                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper011::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
//		MMU.SetVROM_8K_Bank( 1 );
	}
	MMU.SetVRAM_Mirror( VRAM_VMIRROR );
}

void	Mapper011::Write( WORD addr, BYTE data )
{
DEBUGOUT( "WR A:%04X D:%02X\n", addr, data );
	MMU.SetPROM_32K_Bank( data );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( data>>4 );
	}
}

