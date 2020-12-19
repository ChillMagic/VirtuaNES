//////////////////////////////////////////////////////////////////////////
// Mapper110                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper110::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0 );
	nes->mmu.SetVROM_8K_Bank( 0 );

	reg0 = 0;
	reg1 = 0;
}
void	Mapper110::WriteLow( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x4100:
			reg1 = data & 0x07;
			break;
		case	0x4101:
			switch( reg1 ) {
				case	5:
					nes->mmu.SetPROM_32K_Bank( data );
					break;
				case	0:
					reg0 = data & 0x01;
					nes->mmu.SetVROM_8K_Bank( reg0 );
					break;
				case	2:
					reg0 = data;
					nes->mmu.SetVROM_8K_Bank( reg0 );
					break;
				case	4:
					reg0 = reg0 | (data<<1);
					nes->mmu.SetVROM_8K_Bank( reg0 );
					break;
				case	6:
					reg0 = reg0 | (data<<2);
					nes->mmu.SetVROM_8K_Bank( reg0 );
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void	Mapper110::SaveState( LPBYTE p )
{
	p[ 0] = reg0;
	p[ 1] = reg1;
}

void	Mapper110::LoadState( LPBYTE p )
{
	reg0 = p[ 0];
	reg1 = p[ 1];
}
