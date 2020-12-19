﻿//////////////////////////////////////////////////////////////////////////
// Mapper101  Jaleco(Urusei Yatsura)                                    //
//////////////////////////////////////////////////////////////////////////
void	Mapper101::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, 2, 3 );
	nes->mmu.SetVROM_8K_Bank( 0 );
}

void	Mapper101::WriteLow( WORD addr, BYTE data )
{
	if( addr >= 0x6000 ) {
		nes->mmu.SetVROM_8K_Bank( data&0x03 );
	}
}

void	Mapper101::Write( WORD addr, BYTE data )
{
	nes->mmu.SetVROM_8K_Bank( data&0x03 );
}
