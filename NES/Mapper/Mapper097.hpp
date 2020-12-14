//////////////////////////////////////////////////////////////////////////
// Mapper097  Irem 74161                                                //
//////////////////////////////////////////////////////////////////////////
void	Mapper097::Reset()
{
	MMU.SetPROM_32K_Bank( MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1, 0, 1 );

	if( MMU.VROM_8K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper097::Write( WORD addr, BYTE data )
{
	if( addr < 0xC000 ) {
		MMU.SetPROM_16K_Bank( 6, data & 0x0F );

		if( data & 0x80 ) MMU.SetVRAM_Mirror( VRAM_VMIRROR );
		else		  MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	}
}
