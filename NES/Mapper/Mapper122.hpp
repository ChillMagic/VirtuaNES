//////////////////////////////////////////////////////////////////////////
// Mapper122/184  SunSoft-1                                             //
//////////////////////////////////////////////////////////////////////////
void	Mapper122::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, 2, 3 );
}

void	Mapper122::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x6000 ) {
		nes->mmu.SetVROM_4K_Bank( 0,  data & 0x07 );
		nes->mmu.SetVROM_4K_Bank( 4, (data & 0x70)>>4 );
	}
}
