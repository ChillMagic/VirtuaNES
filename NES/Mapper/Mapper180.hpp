//////////////////////////////////////////////////////////////////////////
// Mapper180  Nichibutsu                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper180::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper180::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_16K_Bank( 6, data&0x07 );
}
