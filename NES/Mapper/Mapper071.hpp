//////////////////////////////////////////////////////////////////////////
// Mapper071  Camerica                                                  //
//////////////////////////////////////////////////////////////////////////
void	Mapper071::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
}

void	Mapper071::WriteLow( WORD addr, BYTE data )
{
	if( (addr&0xE000)==0x6000 ) {
		nes->mmu.SetPROM_16K_Bank( 4, data );
	}
}

void	Mapper071::Write( WORD addr, BYTE data )
{
	switch( addr&0xF000 ) {
		case	0x9000:
			if( data&0x10 ) nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4H );
			else		nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4L );
			break;

		case	0xC000:
		case	0xD000:
		case	0xE000:
		case	0xF000:
			nes->mmu.SetPROM_16K_Bank( 4, data );
			break;
	}
}

