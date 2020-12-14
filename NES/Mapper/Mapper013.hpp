//////////////////////////////////////////////////////////////////////////
// Mapper013  CPROM                                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper013::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, 2, 3 );
	MMU.SetCRAM_4K_Bank( 0, 0 );
	MMU.SetCRAM_4K_Bank( 4, 0 );
}

void	Mapper013::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_32K_Bank( (data&0x30)>>4 );
	MMU.SetCRAM_4K_Bank( 4, data&0x03 );
}

