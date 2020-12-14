//////////////////////////////////////////////////////////////////////////
// Mapper140                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper140::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper140::WriteLow( WORD addr, BYTE data )
{
	MMU.SetPROM_32K_Bank( (data&0xF0)>>4 );
	MMU.SetVROM_8K_Bank( data&0x0F );
}

