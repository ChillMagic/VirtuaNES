//////////////////////////////////////////////////////////////////////////
// Mapper194 迷宮寺院ダババ                                             //
//////////////////////////////////////////////////////////////////////////

void	Mapper194::Reset()
{
	nes->mmu.SetPROM_32K_Bank( nes->mmu.PROM_32K_SIZE-1 );
}

void	Mapper194::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_8K_Bank( 3, data );
}
