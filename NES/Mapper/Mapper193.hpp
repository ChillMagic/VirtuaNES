//////////////////////////////////////////////////////////////////////////
// Mapper193 MEGA SOFT (NTDEC) : Fighting Hero                          //
//////////////////////////////////////////////////////////////////////////

void    Mapper193::Reset()
{
	nes->mmu.SetPROM_32K_Bank( nes->mmu.PROM_32K_SIZE-1 );
	if( nes->mmu.VROM_1K_SIZE ) {
		nes->mmu.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper193::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x6000:
			nes->mmu.SetVROM_2K_Bank( 0, ((data>>1)&0x7e)+0 );
			nes->mmu.SetVROM_2K_Bank( 2, ((data>>1)&0x7e)+1 );
			break;
		case	0x6001:
			nes->mmu.SetVROM_2K_Bank( 4, data>>1 );
			break;
		case	0x6002:
			nes->mmu.SetVROM_2K_Bank( 6, data>>1 );
			break;
		case	0x6003:
			nes->mmu.SetPROM_32K_Bank( data );
			break;
	}
}
