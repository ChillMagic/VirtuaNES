//////////////////////////////////////////////////////////////////////////
// Mapper133  SACHEN CHEN                                             //
//////////////////////////////////////////////////////////////////////////
void	Mapper133::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper133::WriteLow( WORD addr, BYTE data )
{
	if( addr == 0x4120 ) {
		MMU.SetPROM_32K_Bank( (data&0x04)>>2 );
		MMU.SetVROM_8K_Bank( data & 0x03 );
	}
	MMU.CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
}

