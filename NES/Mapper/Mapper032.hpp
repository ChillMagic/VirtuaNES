//////////////////////////////////////////////////////////////////////////
// Mapper032  Irem G101                                                 //
//////////////////////////////////////////////////////////////////////////
void	Mapper032::Reset()
{
	patch = 0;
	reg = 0;

	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}

	DWORD	crc = nes->rom->GetPROM_CRC();

	// For Major League(J)
	if( crc == 0xc0fed437 ) {
		patch = 1;
	}
	// For Ai Sensei no Oshiete - Watashi no Hoshi(J)
	if( crc == 0xfd3fc292 ) {
		nes->mmu.SetPROM_32K_Bank( 30, 31, 30, 31 );
	}
}

void	Mapper032::Write( WORD addr, BYTE data )
{
	switch( addr & 0xF000 ) {
		case	0x8000:
			if( reg & 0x02 ) {
				nes->mmu.SetPROM_8K_Bank( 6, data );
			} else {
				nes->mmu.SetPROM_8K_Bank( 4, data );
			}
			break;

		case	0x9000:
			reg = data;
			if( data & 0x01 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			break;

		case	0xA000:
			nes->mmu.SetPROM_8K_Bank( 5, data );
			break;
	}

	switch( addr & 0xF007 ) {
		case	0xB000:
		case	0xB001:
		case	0xB002:
		case	0xB003:
		case	0xB004:
		case	0xB005:
			nes->mmu.SetVROM_1K_Bank( addr & 0x0007, data );
			break;
		case	0xB006:
			nes->mmu.SetVROM_1K_Bank( 6, data );

			if( patch && (data & 0x40) ) {
				nes->mmu.SetVRAM_Mirror( 0, 0, 0, 1 );
			}
			break;
		case	0xB007:
			nes->mmu.SetVROM_1K_Bank( 7, data );

			if( patch && (data & 0x40) ) {
				nes->mmu.SetVRAM_Mirror( 0, 0, 0, 0 );
			}
			break;
	}
}

void	Mapper032::SaveState( LPBYTE p )
{
	p[0] = reg;
}

void	Mapper032::LoadState( LPBYTE p )
{
	reg = p[0];
}
