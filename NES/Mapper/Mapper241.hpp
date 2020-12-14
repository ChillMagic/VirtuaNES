//////////////////////////////////////////////////////////////////////////
// Mapper241  Fon Serm Bon                                              //
//////////////////////////////////////////////////////////////////////////
void    Mapper241::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper241::Write( WORD addr, BYTE data )
{
	if( addr == 0x8000 ) {
		MMU.SetPROM_32K_Bank( data );
	}
}

