//////////////////////////////////////////////////////////////////////////
// Mapper094  Capcom 74161/32                                           //
//////////////////////////////////////////////////////////////////////////
void	Mapper094::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
}

void	Mapper094::Write( WORD addr, BYTE data )
{
	if( (addr&0xFFF0) == 0xFF00 ) {
		MMU.SetPROM_16K_Bank( 4, (data>>2)&0x7 );
	}
}
