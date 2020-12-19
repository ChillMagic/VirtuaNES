//////////////////////////////////////////////////////////////////////////
// Mapper108                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper108::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0xC,0xD,0xE,0xF );
	nes->mmu.SetPROM_8K_Bank( 3, 0 );
}

void	Mapper108::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_8K_Bank( 3, data );
}
