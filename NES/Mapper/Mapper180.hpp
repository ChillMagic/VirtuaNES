//////////////////////////////////////////////////////////////////////////
// Mapper180  Nichibutsu                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper180::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper180::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_16K_Bank( 6, data&0x07 );
}
