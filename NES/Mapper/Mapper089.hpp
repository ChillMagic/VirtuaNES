//////////////////////////////////////////////////////////////////////////
// Mapper089  SunSoft (水戸黄門)                                        //
//////////////////////////////////////////////////////////////////////////
void	Mapper089::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper089::Write( WORD addr, BYTE data )
{
	if( (addr&0xFF00) == 0xC000 ) {
		MMU.SetPROM_16K_Bank( 4, (data&0x70)>>4 );

		MMU.SetVROM_8K_Bank( ((data&0x80)>>4)|(data&0x07) );

		if( data & 0x08 ) MMU.SetVRAM_Mirror( VRAM_MIRROR4H );
		else		  MMU.SetVRAM_Mirror( VRAM_MIRROR4L );
	}
}
