//////////////////////////////////////////////////////////////////////////
// Mapper089  SunSoft (水戸黄門)                                        //
//////////////////////////////////////////////////////////////////////////
void	Mapper089::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper089::Write( WORD addr, BYTE data )
{
	if( (addr&0xFF00) == 0xC000 ) {
		nes->mmu.SetPROM_16K_Bank( 4, (data&0x70)>>4 );

		nes->mmu.SetVROM_8K_Bank( ((data&0x80)>>4)|(data&0x07) );

		if( data & 0x08 ) nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4H );
		else		  nes->mmu.SetVRAM_Mirror( VRAM_MIRROR4L );
	}
}
