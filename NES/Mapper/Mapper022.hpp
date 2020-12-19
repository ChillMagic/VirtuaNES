//////////////////////////////////////////////////////////////////////////
// Mapper022  Konami VRC2 type A                                        //
//////////////////////////////////////////////////////////////////////////
void	Mapper022::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
}

void	Mapper022::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case 0x8000:
			nes->mmu.SetPROM_8K_Bank( 4, data );
			break;

		case 0x9000:
			data &= 0x03;
			if( data == 0 )	     nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			else if( data == 1 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			else if( data == 2 ) nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4H );
			else		     nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4L );
			break;

		case 0xA000:
			nes->mmu.SetPROM_8K_Bank( 5, data );
			break;

		case 0xB000:
			nes->mmu.SetVROM_1K_Bank( 0, data>>1 );
			break;

		case 0xB001:
			nes->mmu.SetVROM_1K_Bank( 1, data>>1 );
			break;

		case 0xC000:
			nes->mmu.SetVROM_1K_Bank( 2, data>>1 );
			break;

		case 0xC001:
			nes->mmu.SetVROM_1K_Bank( 3, data>>1 );
			break;

		case 0xD000:
			nes->mmu.SetVROM_1K_Bank( 4, data>>1 );
			break;

		case 0xD001:
			nes->mmu.SetVROM_1K_Bank( 5, data>>1 );
			break;

		case 0xE000:
			nes->mmu.SetVROM_1K_Bank( 6, data>>1 );
			break;

		case 0xE001:
			nes->mmu.SetVROM_1K_Bank( 7, data>>1 );
			break;
	}
}
