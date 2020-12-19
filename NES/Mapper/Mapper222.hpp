//////////////////////////////////////////////////////////////////////////
// Mapper222                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper222::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
	nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
}

void	Mapper222::Write( WORD addr, BYTE data )
{
	switch( addr & 0xF003 ) {
		case	0x8000:
			nes->mmu.SetPROM_8K_Bank( 4, data );
			break;
		case	0xA000:
			nes->mmu.SetPROM_8K_Bank( 5, data );
			break;
		case	0xB000:
			nes->mmu.SetVROM_1K_Bank( 0, data );
			break;
		case	0xB002:
			nes->mmu.SetVROM_1K_Bank( 1, data );
			break;
		case	0xC000:
			nes->mmu.SetVROM_1K_Bank( 2, data );
			break;
		case	0xC002:
			nes->mmu.SetVROM_1K_Bank( 3, data );
			break;
		case	0xD000:
			nes->mmu.SetVROM_1K_Bank( 4, data );
			break;
		case	0xD002:
			nes->mmu.SetVROM_1K_Bank( 5, data );
			break;
		case	0xE000:
			nes->mmu.SetVROM_1K_Bank( 6, data );
			break;
		case	0xE002:
			nes->mmu.SetVROM_1K_Bank( 7, data );
			break;
	}
}

