//////////////////////////////////////////////////////////////////////////
// Mapper246  Phone Serm Berm                                           //
//////////////////////////////////////////////////////////////////////////

void    Mapper246::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
}

void	Mapper246::WriteLow( WORD addr, BYTE data )
{
	if( addr>=0x6000 && addr<0x8000 ) {
		switch( addr ) {
			case 0x6000:
				nes->mmu.SetPROM_8K_Bank( 4, data );
				break;
			case 0x6001:
				nes->mmu.SetPROM_8K_Bank( 5, data );
				break;
			case 0x6002:
				nes->mmu.SetPROM_8K_Bank( 6, data );
				break;
			case 0x6003: 
				nes->mmu.SetPROM_8K_Bank( 7, data );
				break;
			case 0x6004:
				nes->mmu.SetVROM_2K_Bank(0,data);
				break;
			case 0x6005:
				nes->mmu.SetVROM_2K_Bank(2,data);
				break;
			case 0x6006:
				nes->mmu.SetVROM_2K_Bank(4,data);
				break;
			case 0x6007:
				nes->mmu.SetVROM_2K_Bank(6,data);
				break;
			default:
				nes->mmu.GetCPU_MEM_BANK(addr) = data;
				break;
		}
	}
}
