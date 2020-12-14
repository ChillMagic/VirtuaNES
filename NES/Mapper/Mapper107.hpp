//////////////////////////////////////////////////////////////////////////
// Mapper107  Magic Dragon Mapper                                       //
//////////////////////////////////////////////////////////////////////////
void	Mapper107::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper107::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_32K_Bank( (data>>1)&0x03 );
	MMU.SetVROM_8K_Bank( data&0x07 );
}
