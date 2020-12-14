//////////////////////////////////////////////////////////////////////////
// Mapper201  21-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper201::Reset()
{
//	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	MMU.SetPROM_16K_Bank( 4, 0 );
	MMU.SetPROM_16K_Bank( 6, 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper201::Write( WORD addr, BYTE data )
{
	BYTE	bank = (BYTE)addr & 0x03;
	if( !(addr&0x08) )
		bank = 0;
	MMU.SetPROM_32K_Bank( bank );
	MMU.SetVROM_8K_Bank( bank );
}
