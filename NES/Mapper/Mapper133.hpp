//////////////////////////////////////////////////////////////////////////
// Mapper133  SACHEN CHEN                                             //
//////////////////////////////////////////////////////////////////////////
void	Mapper133::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper133::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x4120 ) {
		nes->mmu.SetPROM_32K_Bank( (data&0x04)>>2 );
		nes->mmu.SetVROM_8K_Bank( data & 0x03 );
	}
	nes->mmu.CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
}

