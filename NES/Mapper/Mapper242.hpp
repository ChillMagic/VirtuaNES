//////////////////////////////////////////////////////////////////////////
// Mapper242  Wai Xing Zhan Shi                                         //
//////////////////////////////////////////////////////////////////////////
void	Mapper242::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );
}

void	Mapper242::Write( WORD addr, BYTE data )
{
	if( addr & 0x01 ) {
		nes->mmu.SetPROM_32K_Bank( (addr&0xF8)>>3 );
	}
}
