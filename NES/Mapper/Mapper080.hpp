//////////////////////////////////////////////////////////////////////////
// Mapper080  Taito X1-005                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper080::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

	if( MMU.VROM_8K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper080::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x7EF0:
			MMU.SetVROM_2K_Bank( 0, (data>>1)&0x3F );
			if( MMU.PROM_8K_SIZE == 32 ) {
				if( data & 0x80 ) {
					MMU.SetVRAM_1K_Bank( 8, 1 );
					MMU.SetVRAM_1K_Bank( 9, 1 );
				} else {
					MMU.SetVRAM_1K_Bank( 8, 0 );
					MMU.SetVRAM_1K_Bank( 9, 0 );
				}
			}
			break;

		case	0x7EF1:
			MMU.SetVROM_2K_Bank( 2, (data>>1)&0x3F );
			if( MMU.PROM_8K_SIZE == 32 ) {
				if( data & 0x80 ) {
					MMU.SetVRAM_1K_Bank( 10, 1 );
					MMU.SetVRAM_1K_Bank( 11, 1 );
				} else {
					MMU.SetVRAM_1K_Bank( 10, 0 );
					MMU.SetVRAM_1K_Bank( 11, 0 );
				}
			}
			break;

		case	0x7EF2:
			MMU.SetVROM_1K_Bank( 4, data );
			break;
		case	0x7EF3:
			MMU.SetVROM_1K_Bank( 5, data );
			break;
		case	0x7EF4:
			MMU.SetVROM_1K_Bank( 6, data );
			break;
		case	0x7EF5:
			MMU.SetVROM_1K_Bank( 7, data );
			break;

		case	0x7EF6:
			if( data & 0x01 ) MMU.SetVRAM_Mirror( VRAM_VMIRROR );
			else		  MMU.SetVRAM_Mirror( VRAM_HMIRROR );
			break;

		case	0x7EFA:
		case	0x7EFB:
			MMU.SetPROM_8K_Bank( 4, data );
			break;
		case	0x7EFC:
		case	0x7EFD:
			MMU.SetPROM_8K_Bank( 5, data );
			break;
		case	0x7EFE:
		case	0x7EFF:
			MMU.SetPROM_8K_Bank( 6, data );
			break;
		default:
			Mapper::WriteLow( addr, data );
			break;
	}
}
