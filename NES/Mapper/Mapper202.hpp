//////////////////////////////////////////////////////////////////////////
// Mapper202  150-in-1                                                  //
//////////////////////////////////////////////////////////////////////////
void	Mapper202::Reset()
{
	MMU.SetPROM_16K_Bank( 4, 6 );
	MMU.SetPROM_16K_Bank( 6, 7 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper202::ExWrite( WORD addr, BYTE data )
{
	if( addr >= 0x4020 ) {
		WriteSub( addr, data );
	}
}

void	Mapper202::WriteLow( WORD addr, BYTE data )
{
	WriteSub( addr, data );
}

void	Mapper202::Write( WORD addr, BYTE data )
{
	WriteSub( addr, data );
}

void	Mapper202::WriteSub( WORD addr, BYTE data )
{
	INT	bank = (addr>>1) & 0x07;

	MMU.SetPROM_16K_Bank( 4, bank );
	if( (addr & 0x0C) == 0x0C ) {
		MMU.SetPROM_16K_Bank( 6, bank+1 );
	} else {
		MMU.SetPROM_16K_Bank( 6, bank );
	}
	MMU.SetVROM_8K_Bank( bank );

	if( addr & 0x01 ) {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	}
}
