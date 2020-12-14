//////////////////////////////////////////////////////////////////////////
// Mapper193 MEGA SOFT (NTDEC) : Fighting Hero                          //
//////////////////////////////////////////////////////////////////////////

void    Mapper193::Reset()
{
	MMU.SetPROM_32K_Bank( MMU.PROM_32K_SIZE-1 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper193::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x6000:
			MMU.SetVROM_2K_Bank( 0, ((data>>1)&0x7e)+0 );
			MMU.SetVROM_2K_Bank( 2, ((data>>1)&0x7e)+1 );
			break;
		case	0x6001:
			MMU.SetVROM_2K_Bank( 4, data>>1 );
			break;
		case	0x6002:
			MMU.SetVROM_2K_Bank( 6, data>>1 );
			break;
		case	0x6003:
			MMU.SetPROM_32K_Bank( data );
			break;
	}
}
