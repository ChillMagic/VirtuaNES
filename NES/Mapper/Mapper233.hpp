//////////////////////////////////////////////////////////////////////////
// Mapper233  42-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper233::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, 2, 3 );
}

void	Mapper233::Write( WORD addr, BYTE data )
{
	if( data & 0x20 ) {
		MMU.SetPROM_8K_Bank( 4, (data&0x1F)*2+0 );
		MMU.SetPROM_8K_Bank( 5, (data&0x1F)*2+1 );
		MMU.SetPROM_8K_Bank( 6, (data&0x1F)*2+0 );
		MMU.SetPROM_8K_Bank( 7, (data&0x1F)*2+1 );
	} else {
		BYTE	bank = (data&0x1E)>>1;

		MMU.SetPROM_8K_Bank( 4, bank*4+0 );
		MMU.SetPROM_8K_Bank( 5, bank*4+1 );
		MMU.SetPROM_8K_Bank( 6, bank*4+2 );
		MMU.SetPROM_8K_Bank( 7, bank*4+3 );
	}

	if( (data&0xC0) == 0x00 ) {
		MMU.SetVRAM_Mirror( 0, 0, 0, 1 );
	} else if( (data&0xC0) == 0x40 ) {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	} else if( (data&0xC0) == 0x80 ) {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_MIRROR4H );
	}
}
