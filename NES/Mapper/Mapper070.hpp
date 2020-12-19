//////////////////////////////////////////////////////////////////////////
// Mapper070  Bandai 74161                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper070::Reset()
{
	patch = 0;

	DWORD	crc = nes->rom->GetPROM_CRC();

	if( crc == 0xa59ca2ef ) {	// Kamen Rider Club(J)
		patch = 1;
		nes->SetRenderMethod( NES::POST_ALL_RENDER );
	}
	if( crc == 0x10bb8f9a ) {	// Family Trainer - Manhattan Police(J)
		patch = 1;
	}
	if( crc == 0x0cd00488 ) {	// Space Shadow(J)
		patch = 1;
	}

	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper070::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_16K_Bank( 4, (data & 0x70)>>4 );
	nes->mmu.SetVROM_8K_Bank( data & 0x0F );

	if( patch ) {
		if( data & 0x80 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
		else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
	} else {
		if( data & 0x80 ) nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4H );
		else		  nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4L );
	}
}
