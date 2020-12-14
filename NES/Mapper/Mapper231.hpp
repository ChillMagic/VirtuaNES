//////////////////////////////////////////////////////////////////////////
// Mapper231  20-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper231::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper231::Write( WORD addr, BYTE data )
{
	if( addr & 0x0020 ) {
		MMU.SetPROM_32K_Bank( (BYTE)(addr>>1) );
	} else {
		BYTE	bank = addr & 0x1E;
		MMU.SetPROM_8K_Bank( 4, bank*2+0 );
		MMU.SetPROM_8K_Bank( 5, bank*2+1 );
		MMU.SetPROM_8K_Bank( 6, bank*2+0 );
		MMU.SetPROM_8K_Bank( 7, bank*2+1 );
	}

	if( addr & 0x0080 ) {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	}
}
