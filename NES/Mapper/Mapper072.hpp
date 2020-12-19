//////////////////////////////////////////////////////////////////////////
// Mapper072  Jaleco/Type1 lower bank switch                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper072::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_8K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper072::Write( WORD addr, BYTE data )
{
	if( data & 0x80 ) {
		nes->mmu.SetPROM_16K_Bank( 4, data&0x0F );
	} else if( data & 0x40 ) {
		nes->mmu.SetVROM_8K_Bank( data&0x0F );
	} else {
		if( addr >= 0xC100 && addr <= 0xC11F && data == 0x20 ) {
//DEBUGOUT( "ADDR:%04X DATA:%02X\n", addr, data );
DEBUGOUT( "SOUND CODE:%02X\n", addr & 0x1F );

			// OSDにするべきか…
			if( ConfigWrapper::GetCCfgSound().bExtraSoundEnable ) {
				ConfigWrapper::DirectSoundEsfAllStop();
				ConfigWrapper::DirectSoundEsfPlay( ESF_MOETENNIS_00+(addr&0x1F) );
			}
		}
	}
}
