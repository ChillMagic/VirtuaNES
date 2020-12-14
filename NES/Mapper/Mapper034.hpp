//////////////////////////////////////////////////////////////////////////
// Mapper034  Nina-1                                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper034::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper034::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x7FFD:
			MMU.SetPROM_32K_Bank( data );
			break;
		case	0x7FFE:
			MMU.SetVROM_4K_Bank( 0, data );
			break;
		case	0x7FFF:
			MMU.SetVROM_4K_Bank( 4, data );
			break;
	}
}

void	Mapper034::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_32K_Bank( data );
}
