//////////////////////////////////////////////////////////////////////////
// Mapper093  SunSoft (Fantasy Zone)                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper093::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper093::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x6000 ) {
		nes->mmu.SetPROM_16K_Bank( 4, data );
	}
}
