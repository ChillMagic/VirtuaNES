//////////////////////////////////////////////////////////////////////////
// Mapper093  SunSoft (Fantasy Zone)                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper093::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	if( MMU.VROM_8K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper093::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x6000 ) {
		MMU.SetPROM_16K_Bank( 4, data );
	}
}
