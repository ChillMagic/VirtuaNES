//////////////////////////////////////////////////////////////////////////
// Mapper222                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper222::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
	MMU.SetVRAM_Mirror( VRAM_VMIRROR );
}

void	Mapper222::Write( WORD addr, BYTE data )
{
	switch( addr & 0xF003 ) {
		case	0x8000:
			MMU.SetPROM_8K_Bank( 4, data );
			break;
		case	0xA000:
			MMU.SetPROM_8K_Bank( 5, data );
			break;
		case	0xB000:
			MMU.SetVROM_1K_Bank( 0, data );
			break;
		case	0xB002:
			MMU.SetVROM_1K_Bank( 1, data );
			break;
		case	0xC000:
			MMU.SetVROM_1K_Bank( 2, data );
			break;
		case	0xC002:
			MMU.SetVROM_1K_Bank( 3, data );
			break;
		case	0xD000:
			MMU.SetVROM_1K_Bank( 4, data );
			break;
		case	0xD002:
			MMU.SetVROM_1K_Bank( 5, data );
			break;
		case	0xE000:
			MMU.SetVROM_1K_Bank( 6, data );
			break;
		case	0xE002:
			MMU.SetVROM_1K_Bank( 7, data );
			break;
	}
}

