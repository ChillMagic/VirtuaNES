//////////////////////////////////////////////////////////////////////////
// Mapper058                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper058::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, 0, 1 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper058::Write( WORD addr, BYTE data )
{
	if( addr & 0x40 ) {
		MMU.SetPROM_16K_Bank( 4, addr&0x07 );
		MMU.SetPROM_16K_Bank( 6, addr&0x07 );
	} else {
		MMU.SetPROM_32K_Bank( (addr&0x06)>>1 );
	}

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( (addr&0x38)>>3 );
	}

	if( data & 0x02 ) MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	else		  MMU.SetVRAM_Mirror( VRAM_HMIRROR );
}

