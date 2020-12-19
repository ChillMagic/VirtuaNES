//////////////////////////////////////////////////////////////////////////
// Mapper201  21-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper201::Reset()
{
//	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetPROM_16K_Bank( 4, 0 );
	nes->mmu.SetPROM_16K_Bank( 6, 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper201::Write( WORD addr, BYTE data )
{
	BYTE	bank = (BYTE)addr & 0x03;
	if( !(addr&0x08) )
		bank = 0;
	nes->mmu.SetPROM_32K_Bank( bank );
	nes->mmu.SetVROM_8K_Bank( bank );
}
