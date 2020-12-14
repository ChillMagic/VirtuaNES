//////////////////////////////////////////////////////////////////////////
// Mapper194 迷宮寺院ダババ                                             //
//////////////////////////////////////////////////////////////////////////

void	Mapper194::Reset()
{
	MMU.SetPROM_32K_Bank( MMU.PROM_32K_SIZE-1 );
}

void	Mapper194::Write( WORD addr, BYTE data )
{
	MMU.SetPROM_8K_Bank( 3, data );
}
