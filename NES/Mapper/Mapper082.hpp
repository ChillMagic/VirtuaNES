//////////////////////////////////////////////////////////////////////////
// Mapper082  Taito C075                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper082::Reset()
{
	reg = 0;

	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}

	nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
}

void	Mapper082::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x7EF0:
			if( reg ) {
				nes->mmu.SetVROM_2K_Bank( 4, data>>1 );
			} else {
				nes->mmu.SetVROM_2K_Bank( 0, data>>1 );
			}
			break;

		case	0x7EF1:
			if( reg ) {
				nes->mmu.SetVROM_2K_Bank( 6, data>>1 );
			} else {
				nes->mmu.SetVROM_2K_Bank( 2, data>>1 );
			}
			break;

		case	0x7EF2:
			if( reg ) nes->mmu.SetVROM_1K_Bank( 0, data );
			else	  nes->mmu.SetVROM_1K_Bank( 4, data );
			break;
		case	0x7EF3:
			if( reg ) nes->mmu.SetVROM_1K_Bank( 1, data );
			else	  nes->mmu.SetVROM_1K_Bank( 5, data );
			break;
		case	0x7EF4:
			if( reg ) nes->mmu.SetVROM_1K_Bank( 2, data );
			else	  nes->mmu.SetVROM_1K_Bank( 6, data );
			break;
		case	0x7EF5:
			if( reg ) nes->mmu.SetVROM_1K_Bank( 3, data );
			else	  nes->mmu.SetVROM_1K_Bank( 7, data );
			break;

		case	0x7EF6:
			reg = data & 0x02;
			if( data & 0x01 ) nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			else		  nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			break;

		case	0x7EFA:
			nes->mmu.SetPROM_8K_Bank( 4, data>>2 );
			break;
		case	0x7EFB:
			nes->mmu.SetPROM_8K_Bank( 5, data>>2 );
			break;
		case	0x7EFC:
			nes->mmu.SetPROM_8K_Bank( 6, data>>2 );
			break;
		default:
			Mapper::WriteLow( addr, data );
			break;
	}
}

void	Mapper082::SaveState( LPBYTE p )
{
	p[0] = reg;
}

void	Mapper082::LoadState( LPBYTE p )
{
	reg = p[0];
}
