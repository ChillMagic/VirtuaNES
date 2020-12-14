//////////////////////////////////////////////////////////////////////////
// Mapper108                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper108::Reset()
{
	MMU.SetPROM_32K_Bank( 0xC,0xD,0xE,0xF );
	MMU.SetPROM_8K_Bank( 3, 0 );
}

void	Mapper108::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_8K_Bank( 3, data );
}
