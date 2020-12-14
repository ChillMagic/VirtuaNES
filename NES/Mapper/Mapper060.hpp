//////////////////////////////////////////////////////////////////////////
// Mapper060                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper060::Reset()
{
	patch = 0;

	DWORD	crc = nes->rom->GetPROM_CRC();
	if( crc == 0xf9c484a0 ) {	// Reset Based 4-in-1(Unl)
		MMU.SetPROM_16K_Bank( 4, game_sel );
		MMU.SetPROM_16K_Bank( 6, game_sel );
		MMU.SetVROM_8K_Bank( game_sel );
		game_sel++;
		game_sel &= 3;
	} else {
		patch = 1;
		MMU.SetPROM_32K_Bank( 0 );
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper060::Write( WORD addr, BYTE data )
{
	if( patch ) {
		if( addr & 0x80 ) {
			MMU.SetPROM_16K_Bank( 4, (addr&0x70)>>4 );
			MMU.SetPROM_16K_Bank( 6, (addr&0x70)>>4 );
		} else {
			MMU.SetPROM_32K_Bank( (addr&0x70)>>5 );
		}

		MMU.SetVROM_8K_Bank( addr&0x07 );

		if( data & 0x08 ) MMU.SetVRAM_Mirror( VRAM_VMIRROR );
		else		  MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	}
}

