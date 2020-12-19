//////////////////////////////////////////////////////////////////////////
// Mapper034  Nina-1                                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper034::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper034::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x7FFD:
			nes->mmu.SetPROM_32K_Bank( data );
			break;
		case	0x7FFE:
			nes->mmu.SetVROM_4K_Bank( 0, data );
			break;
		case	0x7FFF:
			nes->mmu.SetVROM_4K_Bank( 4, data );
			break;
	}
}

void	Mapper034::Write( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_32K_Bank( data );
}
