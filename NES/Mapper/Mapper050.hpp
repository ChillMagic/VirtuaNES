//////////////////////////////////////////////////////////////////////////
// Mapper050  SMB2J                                                     //
//////////////////////////////////////////////////////////////////////////
void	Mapper050::Reset()
{
	irq_enable = 0;
	MMU.SetPROM_8K_Bank( 3, 15 );
	MMU.SetPROM_8K_Bank( 4, 8 );
	MMU.SetPROM_8K_Bank( 5, 9 );
	MMU.SetPROM_8K_Bank( 6, 0 );
	MMU.SetPROM_8K_Bank( 7, 11 );
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper050::ExWrite( WORD addr, BYTE data )
{
	if( (addr & 0xE060) == 0x4020 ) {
		if( addr & 0x0100 ) {
			irq_enable = data & 0x01;
			nes->cpu->ClrIRQ( IRQ_MAPPER );
		} else {
			MMU.SetPROM_8K_Bank( 6, (data&0x08)|((data&0x01)<<2)|((data&0x06)>>1) );
		}
	}
}

void	Mapper050::WriteLow( WORD addr, BYTE data )
{
	if( (addr & 0xE060) == 0x4020 ) {
		if( addr & 0x0100 ) {
			irq_enable = data & 0x01;
			nes->cpu->ClrIRQ( IRQ_MAPPER );
		} else {
			MMU.SetPROM_8K_Bank( 6, (data&0x08)|((data&0x01)<<2)|((data&0x06)>>1) );
		}
	}
}

void	Mapper050::HSync( INT scanline )
{
	if( irq_enable ) {
		if( scanline == 21 ) {
//			nes->cpu->IRQ();
			nes->cpu->SetIRQ( IRQ_MAPPER );
		}
	}
}

void	Mapper050::SaveState( LPBYTE p )
{
	p[0] = irq_enable;
}

void	Mapper050::LoadState( LPBYTE p )
{
	irq_enable = p[0];
}

