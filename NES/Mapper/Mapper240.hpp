//////////////////////////////////////////////////////////////////////////
// Mapper240  Gen Ke Le Zhuan                                           //
//////////////////////////////////////////////////////////////////////////

void    Mapper240::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper240::WriteLow( WORD addr, BYTE data )
{
	if( addr>=0x4020 && addr<0x6000 ) {
		MMU.SetPROM_32K_Bank( (data&0xF0)>>4 );
		MMU.SetVROM_8K_Bank(data&0xF);
	}
}
