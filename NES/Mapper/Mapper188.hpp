//////////////////////////////////////////////////////////////////////////
// Mapper188  Bandai Karaoke Studio                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper188::Reset()
{
	if( nes->mmu.PROM_8K_SIZE > 16 ) {
		nes->mmu.SetPROM_32K_Bank( 0, 1, 14, 15 );
	} else {
		nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	}
}

void	Mapper188::Write( WORD addr, BYTE data )
{
	if( data ) {
		if( data & 0x10 ) {
			data &= 0x07;
			nes->mmu.SetPROM_16K_Bank( 4, data );
		} else {
			nes->mmu.SetPROM_16K_Bank( 4, data+8 );
		}
	} else {
		if( nes->mmu.PROM_8K_SIZE == 0x10 ) {
			nes->mmu.SetPROM_16K_Bank( 4, 7 );
		} else {
			nes->mmu.SetPROM_16K_Bank( 4, 8 );
		}
	}
}
