//////////////////////////////////////////////////////////////////////////
// Mapper011  Color Dreams                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper011::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
//		nes->mmu.SetVROM_8K_Bank( 1 );
	}
	nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
}

void	Mapper011::Write( WORD addr, BYTE data )
{
DEBUGOUT( "WR A:%04X D:%02X\n", addr, data );
	nes->mmu.SetPROM_32K_Bank( data );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( data>>4 );
	}
}

