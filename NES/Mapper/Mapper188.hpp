//////////////////////////////////////////////////////////////////////////
// Mapper188  Bandai Karaoke Studio                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper188::Reset()
{
	if( MMU.PROM_8K_SIZE > 16 ) {
		MMU.SetPROM_32K_Bank( 0, 1, 14, 15 );
	} else {
		MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	}
}

void	Mapper188::Write( WORD addr, BYTE data )
{
	if( data ) {
		if( data & 0x10 ) {
			data &= 0x07;
			MMU.SetPROM_16K_Bank( 4, data );
		} else {
			MMU.SetPROM_16K_Bank( 4, data+8 );
		}
	} else {
		if( MMU.PROM_8K_SIZE == 0x10 ) {
			MMU.SetPROM_16K_Bank( 4, 7 );
		} else {
			MMU.SetPROM_16K_Bank( 4, 8 );
		}
	}
}
