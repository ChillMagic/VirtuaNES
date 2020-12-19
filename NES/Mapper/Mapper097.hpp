//////////////////////////////////////////////////////////////////////////
// Mapper097  Irem 74161                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper097::Reset()
{
	nes->mmu.SetPROM_32K_Bank( nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1, 0, 1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper097::Write( WORD addr, BYTE data )
{
	if( addr < 0xC000 ) {
		nes->mmu.SetPROM_16K_Bank( 6, data & 0x0F );

		if( data & 0x80 ) nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
		else		  nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
	}
}
