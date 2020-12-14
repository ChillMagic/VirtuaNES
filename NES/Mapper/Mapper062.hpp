//////////////////////////////////////////////////////////////////////////
// Mapper062                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper062::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper062::Write( WORD addr, BYTE data )
{
	switch( addr & 0xFF00 ) {
		case	0x8100:
			MMU.SetPROM_8K_Bank( 4, data );
			MMU.SetPROM_8K_Bank( 5, data+1 );
			break;
		case	0x8500:
			MMU.SetPROM_8K_Bank( 4, data );
			break;
		case	0x8700:
			MMU.SetPROM_8K_Bank( 5, data );
			break;
	MMU.SetVROM_1K_Bank( 0, data+0 );
	MMU.SetVROM_1K_Bank( 1, data+1 );
	MMU.SetVROM_1K_Bank( 2, data+2 );
	MMU.SetVROM_1K_Bank( 3, data+3 );
	MMU.SetVROM_1K_Bank( 4, data+4 );
	MMU.SetVROM_1K_Bank( 5, data+5 );
	MMU.SetVROM_1K_Bank( 6, data+6 );
	MMU.SetVROM_1K_Bank( 7, data+7 );
	}
}

