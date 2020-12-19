//////////////////////////////////////////////////////////////////////////
// Mapper140                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper140::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper140::WriteLow( WORD addr, BYTE data )
{
	nes->mmu.SetPROM_32K_Bank( (data&0xF0)>>4 );
	nes->mmu.SetVROM_8K_Bank( data&0x0F );
}

