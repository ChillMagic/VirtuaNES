//////////////////////////////////////////////////////////////////////////
// Mapper077  Irem Early Mapper #0                                      //
//////////////////////////////////////////////////////////////////////////
void	Mapper077::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );

	nes->mmu.SetVROM_2K_Bank( 0, 0 );
	nes->mmu.SetCRAM_2K_Bank( 2, 1 );
	nes->mmu.SetCRAM_2K_Bank( 4, 2 );
	nes->mmu.SetCRAM_2K_Bank( 6, 3 );
}

void	Mapper077::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_32K_Bank( data & 0x07 );

	nes->mmu.SetVROM_2K_Bank( 0, (data & 0xF0)>>4 );
}
