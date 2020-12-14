//////////////////////////////////////////////////////////////////////////
// Mapper076  Namcot 109 (女神転生)                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper076::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );

	if( MMU.VROM_1K_SIZE >= 8 ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper076::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x8000:
			reg = data;
			break;
		case	0x8001:
			switch( reg & 0x07 ) {
				case	2:
					MMU.SetVROM_2K_Bank( 0, data );
					break;
				case	3:
					MMU.SetVROM_2K_Bank( 2, data );
					break;
				case	4:
					MMU.SetVROM_2K_Bank( 4, data );
					break;
				case	5:
					MMU.SetVROM_2K_Bank( 6, data );
					break;
				case	6:
					MMU.SetPROM_8K_Bank( 4, data );
					break;
				case	7:
					MMU.SetPROM_8K_Bank( 5, data );
					break;
			}
			break;
	}
}

void	Mapper076::SaveState( LPBYTE p )
{
	p[0] = reg;
}

void	Mapper076::LoadState( LPBYTE p )
{
	reg = p[0];
}
