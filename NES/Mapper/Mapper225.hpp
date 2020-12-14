//////////////////////////////////////////////////////////////////////////
// Mapper225  72-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper225::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, 2, 3 );

	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}
}

void	Mapper225::Write( WORD addr, BYTE data )
{
	BYTE prg_bank = (addr & 0x0F80) >> 7;
	BYTE chr_bank = addr & 0x003F;

	MMU.SetVROM_1K_Bank(0,(chr_bank*8+0));
	MMU.SetVROM_1K_Bank(1,(chr_bank*8+1));
	MMU.SetVROM_1K_Bank(2,(chr_bank*8+2));
	MMU.SetVROM_1K_Bank(3,(chr_bank*8+3));
	MMU.SetVROM_1K_Bank(4,(chr_bank*8+4));
	MMU.SetVROM_1K_Bank(5,(chr_bank*8+5));
	MMU.SetVROM_1K_Bank(6,(chr_bank*8+6));
	MMU.SetVROM_1K_Bank(7,(chr_bank*8+7));

	if( addr & 0x2000 ) {
		MMU.SetVRAM_Mirror( VRAM_HMIRROR );
	} else {
		MMU.SetVRAM_Mirror( VRAM_VMIRROR );
	}

	if( addr & 0x1000 ) {
		// 16KBbank
		if( addr & 0x0040 ) {
			MMU.SetPROM_8K_Bank(4,(prg_bank*4+2));
			MMU.SetPROM_8K_Bank(5,(prg_bank*4+3));
			MMU.SetPROM_8K_Bank(6,(prg_bank*4+2));
			MMU.SetPROM_8K_Bank(7,(prg_bank*4+3));
		} else {
			MMU.SetPROM_8K_Bank(4,(prg_bank*4+0));
			MMU.SetPROM_8K_Bank(5,(prg_bank*4+1));
			MMU.SetPROM_8K_Bank(6,(prg_bank*4+0));
			MMU.SetPROM_8K_Bank(7,(prg_bank*4+1));
		}
	} else {
		MMU.SetPROM_8K_Bank(4,(prg_bank*4+0));
		MMU.SetPROM_8K_Bank(5,(prg_bank*4+1));
		MMU.SetPROM_8K_Bank(6,(prg_bank*4+2));
		MMU.SetPROM_8K_Bank(7,(prg_bank*4+3));
	}
}
