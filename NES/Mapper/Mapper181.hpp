//////////////////////////////////////////////////////////////////////////
// Mapper181  Hacker International Type2                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper181::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper181::WriteLow( WORD addr, BYTE data )
{
//DEBUGOUT( "$%04X:$%02X\n", addr, data );
	if( addr == 0x4120 ) {
		MMU.SetPROM_32K_Bank( (data & 0x08) >> 3 );
		MMU.SetVROM_8K_Bank( data & 0x07 );
	}
}

