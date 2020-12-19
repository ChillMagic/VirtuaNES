//////////////////////////////////////////////////////////////////////////
// Mapper240  Gen Ke Le Zhuan                                           //
//////////////////////////////////////////////////////////////////////////

void    Mapper240::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper240::WriteLow( WORD addr, BYTE data )
{
	if( addr>=0x4020 && addr<0x6000 ) {
		nes->mmu.SetPROM_32K_Bank( (data&0xF0)>>4 );
		nes->mmu.SetVROM_8K_Bank(data&0xF);
	}
}
