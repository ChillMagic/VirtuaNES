//////////////////////////////////////////////////////////////////////////
// Mapper088  Namcot 118                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper088::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

	if( MMU.VROM_1K_SIZE >= 8 ) {
		MMU.SetVROM_8K_Bank( 0 );
	}

	patch = 0;

	DWORD	crc = nes->rom->GetPROM_CRC();
	if( crc == 0xc1b6b2a6 ) { // Devil Man(J)
		patch = 1;
		nes->SetRenderMethod( NES::POST_RENDER );
	}
	if( crc == 0xd9803a35 ) {	// Quinty(J)
		nes->SetRenderMethod( NES::POST_RENDER );
	}
}

void	Mapper088::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x8000:
			reg = data;
			if( patch ) {
				if( data&0x40 ) MMU.SetVRAM_Mirror( VRAM_MIRROR4H );
				else	        MMU.SetVRAM_Mirror( VRAM_MIRROR4L );
			}
			break;
		case	0x8001:
			switch( reg & 0x07 ) {
				case	0:
					MMU.SetVROM_2K_Bank( 0, data>>1 );
					break;
				case	1:
					MMU.SetVROM_2K_Bank( 2, data>>1 );
					break;
				case	2:
					MMU.SetVROM_1K_Bank( 4, data+0x40 );
					break;
				case	3:
					MMU.SetVROM_1K_Bank( 5, data+0x40 );
					break;
				case	4:
					MMU.SetVROM_1K_Bank( 6, data+0x40 );
					break;
				case	5:
					MMU.SetVROM_1K_Bank( 7, data+0x40 );
					break;
				case	6:
					MMU.SetPROM_8K_Bank( 4, data );
					break;
				case	7:
					MMU.SetPROM_8K_Bank( 5, data );
					break;
			}
			break;
		case	0xC000:
			if( data ) MMU.SetVRAM_Mirror( VRAM_MIRROR4H );
			else	   MMU.SetVRAM_Mirror( VRAM_MIRROR4L );
			break;
	}
}

void	Mapper088::SaveState( LPBYTE p )
{
	p[0] = reg;
}

void	Mapper088::LoadState( LPBYTE p )
{
	reg = p[0];
}
