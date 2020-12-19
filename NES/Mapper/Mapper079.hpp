//////////////////////////////////////////////////////////////////////////
// Mapper079  Nina-3                                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper079::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );

	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper079::WriteLow( WORD addr, BYTE data )
{
	if( addr&0x0100 ) {
		nes->mmu.SetPROM_32K_Bank( (data>>3)&0x01 );
		nes->mmu.SetVROM_8K_Bank( data&0x07 );
	}
}
