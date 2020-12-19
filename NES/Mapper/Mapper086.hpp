//////////////////////////////////////////////////////////////////////////
// Mapper086  Jaleco Early Mapper #2                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper086::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, 2, 3 );
	nes->mmu.SetVROM_8K_Bank( 0 );

	reg = 0xFF;
	cnt = 0;
}

void	Mapper086::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x6000 ) {
		nes->mmu.SetPROM_32K_Bank( (data&0x30)>>4 );

		nes->mmu.SetVROM_8K_Bank( (data&0x03)|((data & 0x40)>>4) );
	}
	if( addr == 0x7000 ) {
		if( !(reg&0x10) && (data&0x10) && !cnt ) {
//DEBUGOUT( "WR:$%02X\n", data );
			if( (data&0x0F) == 0		// Strike
			 || (data&0x0F) == 5 ) {	// Foul
				cnt = 60;		// 次の発声を1秒程禁止する
			}

			// OSDにするべきか…
			if( ConfigWrapper::GetCCfgSound().bExtraSoundEnable ) {
				ConfigWrapper::DirectSoundEsfAllStop();
				ConfigWrapper::DirectSoundEsfPlay( ESF_MOEPRO_STRIKE+(data&0x0F) );
			}
		}
		reg = data;
	}
}

void	Mapper086::VSync()
{
	if( cnt ) {
		cnt--;
	}
}

