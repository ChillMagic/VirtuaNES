//////////////////////////////////////////////////////////////////////////
// Mapper077  Irem Early Mapper #0                                      //
//////////////////////////////////////////////////////////////////////////
void	Mapper077::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );

	MMU.SetVROM_2K_Bank( 0, 0 );
	MMU.SetCRAM_2K_Bank( 2, 1 );
	MMU.SetCRAM_2K_Bank( 4, 2 );
	MMU.SetCRAM_2K_Bank( 6, 3 );
}

void	Mapper077::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_32K_Bank( data & 0x07 );

	MMU.SetVROM_2K_Bank( 0, (data & 0xF0)>>4 );
}
