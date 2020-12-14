//////////////////////////////////////////////////////////////////////////
// Mapper099  VS-Unisystem                                              //
//////////////////////////////////////////////////////////////////////////

void	Mapper099::Reset()
{
	// set CPU bank pointers
	if( MMU.PROM_8K_SIZE > 2 ) {
		MMU.SetPROM_32K_Bank( 0, 1, 2, 3 );
	} else if( MMU.PROM_8K_SIZE > 1 ) {
		MMU.SetPROM_32K_Bank( 0, 1, 0, 1 );
	} else {
		MMU.SetPROM_32K_Bank( 0, 0, 0, 0 );
	}

	// set VROM bank
	if( MMU.VROM_1K_SIZE ) {
		MMU.SetVROM_8K_Bank( 0 );
	}

	coin = 0;
}

BYTE	Mapper099::ExRead( WORD addr )
{
	if( addr == 0x4020 ) {
		return	coin;
	}

	return	addr>>8;
}

void	Mapper099::ExWrite( WORD addr, BYTE data )
{
	if( addr == 0x4016 ) {
		if( data & 0x04 ) {
			MMU.SetVROM_8K_Bank( 1 );
		} else {
			MMU.SetVROM_8K_Bank( 0 );
		}

		if( nes->rom->GetPROM_CRC() == 0xC99EC059 ) {	// VS Raid on Bungeling Bay(J)
			if( data & 0x02 ) {
				nes->cpu->SetIRQ( IRQ_MAPPER );
			} else {
				nes->cpu->ClrIRQ( IRQ_MAPPER );
			}
		}
	}

	if( addr == 0x4020 ) {
		coin = data;
	}
}
