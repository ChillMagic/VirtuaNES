//////////////////////////////////////////////////////////////////////////
// Mapper061                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper061::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
}

void	Mapper061::Write( WORD addr, BYTE data )
{
	switch( addr & 0x30 ) {
		case	0x00:
		case	0x30:
			nes->mmu.SetPROM_32K_Bank( addr & 0x0F );
			break;
		case	0x10:
		case	0x20:
			nes->mmu.SetPROM_16K_Bank( 4, ((addr & 0x0F)<<1)|((addr&0x20)>>4) );
			nes->mmu.SetPROM_16K_Bank( 6, ((addr & 0x0F)<<1)|((addr&0x20)>>4) );
			break;
	}

	if( addr & 0x80 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
	else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
}

