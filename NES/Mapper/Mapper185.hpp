//////////////////////////////////////////////////////////////////////////
// Mapper185  Character disable protect                                 //
//////////////////////////////////////////////////////////////////////////
void	Mapper185::Reset()
{
	switch( MMU.PROM_16K_SIZE ) {
		case	1:	// 16K only
			MMU.SetPROM_16K_Bank( 4, 0 );
			MMU.SetPROM_16K_Bank( 6, 0 );
			break;
		case	2:	// 32K
			MMU.SetPROM_32K_Bank( 0 );
			break;
	}

	for( INT i = 0; i < 0x400; i++ ) {
		MMU.VRAM[0x800+i] = 0xFF;
	}

	patch = 0;

	DWORD	crc = nes->rom->GetPROM_CRC();
	if( crc == 0xb36457c7 ) {	// Spy vs Spy(J)
		patch = 1;
	}
}

void	Mapper185::Write( WORD addr, BYTE data )
{
	if( (!patch && (data&0x03)) || (patch && data == 0x21) ) {
		MMU.SetVROM_8K_Bank( 0 );
	} else {
		MMU.SetVRAM_1K_Bank( 0, 2 );	// use vram bank 2
		MMU.SetVRAM_1K_Bank( 1, 2 );
		MMU.SetVRAM_1K_Bank( 2, 2 );
		MMU.SetVRAM_1K_Bank( 3, 2 );
		MMU.SetVRAM_1K_Bank( 4, 2 );
		MMU.SetVRAM_1K_Bank( 5, 2 );
		MMU.SetVRAM_1K_Bank( 6, 2 );
		MMU.SetVRAM_1K_Bank( 7, 2 );
	}
}
