//////////////////////////////////////////////////////////////////////////
// Mapper230  22-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper230::Reset()
{
	if( rom_sw ) {
		rom_sw = 0;
	} else {
		rom_sw = 1;
	}
	if( rom_sw ) {
		MMU.SetPROM_32K_Bank( 0, 1, 14, 15 );
	} else {
		MMU.SetPROM_32K_Bank( 16, 17, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	}
}

void	Mapper230::Write( WORD addr, BYTE data )
{
	if( rom_sw ) {
		MMU.SetPROM_8K_Bank( 4, (data&0x07)*2+0 );
		MMU.SetPROM_8K_Bank( 5, (data&0x07)*2+1 );
	} else {
		if( data & 0x20 ) {
			MMU.SetPROM_8K_Bank( 4, (data&0x1F)*2+16 );
			MMU.SetPROM_8K_Bank( 5, (data&0x1F)*2+17 );
			MMU.SetPROM_8K_Bank( 6, (data&0x1F)*2+16 );
			MMU.SetPROM_8K_Bank( 7, (data&0x1F)*2+17 );
		} else {
			MMU.SetPROM_8K_Bank( 4, (data&0x1E)*2+16 );
			MMU.SetPROM_8K_Bank( 5, (data&0x1E)*2+17 );
			MMU.SetPROM_8K_Bank( 6, (data&0x1E)*2+18 );
			MMU.SetPROM_8K_Bank( 7, (data&0x1E)*2+19 );
		}
		if( data & 0x40 ) {
			MMU.SetVRAM_Mirror( VRAM_VMIRROR );
		} else {
			MMU.SetVRAM_Mirror( VRAM_HMIRROR );
		}
	}
}
