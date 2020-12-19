//////////////////////////////////////////////////////////////////////////
// Mapper062                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper062::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper062::Write( WORD addr, BYTE data )
{
	switch( addr & 0xFF00 ) {
		case	0x8100:
			nes->mmu.SetPROM_8K_Bank( 4, data );
			nes->mmu.SetPROM_8K_Bank( 5, data+1 );
			break;
		case	0x8500:
			nes->mmu.SetPROM_8K_Bank( 4, data );
			break;
		case	0x8700:
			nes->mmu.SetPROM_8K_Bank( 5, data );
			break;
	nes->mmu.SetVROM_1K_Bank( 0, data+0 );
	nes->mmu.SetVROM_1K_Bank( 1, data+1 );
	nes->mmu.SetVROM_1K_Bank( 2, data+2 );
	nes->mmu.SetVROM_1K_Bank( 3, data+3 );
	nes->mmu.SetVROM_1K_Bank( 4, data+4 );
	nes->mmu.SetVROM_1K_Bank( 5, data+5 );
	nes->mmu.SetVROM_1K_Bank( 6, data+6 );
	nes->mmu.SetVROM_1K_Bank( 7, data+7 );
	}
}

