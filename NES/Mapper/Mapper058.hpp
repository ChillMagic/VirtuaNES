//////////////////////////////////////////////////////////////////////////
// Mapper058                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper058::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, 0, 1 );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper058::Write( WORD addr, BYTE data )
{
	if( addr & 0x40 ) {
		nes->mmu.SetPROM_16K_Bank( 4, addr&0x07 );
		nes->mmu.SetPROM_16K_Bank( 6, addr&0x07 );
	} else {
		nes->mmu.SetPROM_32K_Bank( (addr&0x06)>>1 );
	}

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( (addr&0x38)>>3 );
	}

	if( data & 0x02 ) nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
	else		  nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
}

