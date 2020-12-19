//////////////////////////////////////////////////////////////////////////
// Mapper241  Fon Serm Bon                                              //
//////////////////////////////////////////////////////////////////////////
void    Mapper241::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper241::Write( WORD addr, BYTE data )
{
	if( addr == 0x8000 ) {
		nes->mmu.SetPROM_32K_Bank( data );
	}
}

