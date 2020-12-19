//////////////////////////////////////////////////////////////////////////
// Mapper066  Bandai 74161                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper066::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetVROM_8K_Bank( 0 );

//	if( nes->rom->GetPROM_CRC() == 0xe30552db ) {	// Paris-Dakar Rally Special
//		nes->SetFrameIRQmode( FALSE );
//	}
}

void	Mapper066::WriteLow( WORD addr, BYTE data )
{
	if( addr >= 0x6000 ) {
		nes->mmu.SetPROM_32K_Bank( (data & 0xF0) >> 4 );
		nes->mmu.SetVROM_8K_Bank( data & 0x0F );
	}
}

void	Mapper066::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_32K_Bank( (data & 0xF0) >> 4 );
	nes->mmu.SetVROM_8K_Bank( data & 0x0F );
}
