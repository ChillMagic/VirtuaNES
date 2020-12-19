//////////////////////////////////////////////////////////////////////////
// Mapper107  Magic Dragon Mapper                                       //
//////////////////////////////////////////////////////////////////////////
void	Mapper107::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper107::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_32K_Bank( (data>>1)&0x03 );
	nes->mmu.SetVROM_8K_Bank( data&0x07 );
}
