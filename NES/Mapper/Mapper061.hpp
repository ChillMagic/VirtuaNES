//////////////////////////////////////////////////////////////////////////
// Mapper061                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper061::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
}

void	Mapper061::Write( WORD addr, BYTE data )
{
	switch( addr & 0x30 ) {
		case	0x00:
		case	0x30:
			MMU.SetPROM_32K_Bank( addr & 0x0F );
			break;
		case	0x10:
		case	0x20:
			MMU.SetPROM_16K_Bank( 4, ((addr & 0x0F)<<1)|((addr&0x20)>>4) );
			MMU.SetPROM_16K_Bank( 6, ((addr & 0x0F)<<1)|((addr&0x20)>>4) );
			break;
	}

	if( addr & 0x80 ) MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	else		  MMU.SetVRAM_Mirror( VRAM_VMIRROR );
}

