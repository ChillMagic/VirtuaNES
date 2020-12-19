//////////////////////////////////////////////////////////////////////////
// Mapper092  Jaleco/Type1 Higher bank switch                           //
//////////////////////////////////////////////////////////////////////////
void	Mapper092::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper092::Write( WORD addr, BYTE data )
{
//DEBUGOUT( "A:%04X D:%02X\n", addr, data );

	data = addr & 0xFF;

	if( addr >= 0x9000 ) {
		if( (data & 0xF0) == 0xD0 ) {
			nes->mmu.SetPROM_16K_Bank( 6, data & 0x0F );
		} else if( (data & 0xF0) == 0xE0 ) {
			nes->mmu.SetVROM_8K_Bank( data & 0x0F );
		}
	} else {
		if( (data & 0xF0) == 0xB0 ) {
			nes->mmu.SetPROM_16K_Bank( 6, data & 0x0F );
		} else if( (data & 0xF0) == 0x70 ) {
			nes->mmu.SetVROM_8K_Bank( data & 0x0F );
		} else if( (data & 0xF0) == 0xC0 ) {
			INT	tbl[] = { 3, 4, 5, 6, 0, 1, 2, 7,
					  9,10, 8,11,13,12,14,15 };

			// OSDにするべきか…
			if( ConfigWrapper::GetCCfgSound().bExtraSoundEnable ) {
DEBUGOUT( "CODE %02X\n", data );
				ConfigWrapper::DirectSoundEsfAllStop();
				ConfigWrapper::DirectSoundEsfPlay( ESF_MOEPRO_STRIKE+tbl[data&0x0F] );
			}
		}
	}
}
