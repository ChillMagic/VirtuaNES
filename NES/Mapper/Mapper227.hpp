//////////////////////////////////////////////////////////////////////////
// Mapper227  1200-in-1                                                 //
//////////////////////////////////////////////////////////////////////////
void	Mapper227::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, 0, 1 );
}

void	Mapper227::Write( WORD addr, BYTE data )
{
	BYTE	bank = ((addr&0x0100)>>4)|((addr&0x0078)>>3);

	if( addr & 0x0001 ) {
		MMU.SetPROM_32K_Bank( bank );
	} else {
		if( addr & 0x0004 ) {
			MMU.SetPROM_8K_Bank( 4, bank*4+2 );
			MMU.SetPROM_8K_Bank( 5, bank*4+3 );
			MMU.SetPROM_8K_Bank( 6, bank*4+2 );
			MMU.SetPROM_8K_Bank( 7, bank*4+3 );
		} else {
			MMU.SetPROM_8K_Bank( 4, bank*4+0 );
			MMU.SetPROM_8K_Bank( 5, bank*4+1 );
			MMU.SetPROM_8K_Bank( 6, bank*4+0 );
			MMU.SetPROM_8K_Bank( 7, bank*4+1 );
		}
	}

	if( !(addr & 0x0080) ) {
		if( addr & 0x0200 ) {
			MMU.SetPROM_8K_Bank( 6, (bank&0x1C)*4+14 );
			MMU.SetPROM_8K_Bank( 7, (bank&0x1C)*4+15 );
		} else {
			MMU.SetPROM_8K_Bank( 6, (bank&0x1C)*4+0 );
			MMU.SetPROM_8K_Bank( 7, (bank&0x1C)*4+1 );
		}
	}
	if( addr & 0x0002 ) {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	}
}
