//////////////////////////////////////////////////////////////////////////
// Mapper151 VS-Unisystem                                               //
//////////////////////////////////////////////////////////////////////////
void	Mapper151::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

#if	0
	DWORD	crc = nes->rom->GetPROM_CRC();
	if( crc == 0x1E438D52 ) {
		DirectDraw.SetVsPalette( 7 );	//VS_Goonies
	}
	if( crc == 0xD99A2087 ) {
		DirectDraw.SetVsPalette( 6 );	//VS_Gradius
	}
#endif
}

void	Mapper151::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case 0x8000:
			MMU.SetPROM_8K_Bank( 4,data );
			break;
		case 0xA000:
			MMU.SetPROM_8K_Bank( 5,data );
			break;
		case 0xC000:
			MMU.SetPROM_8K_Bank( 6,data );
			break;
		case 0xE000:
			MMU.SetVROM_4K_Bank( 0, data );
			break;
		case	0xF000:
			MMU.SetVROM_4K_Bank( 4, data );
			break;
	}
}
