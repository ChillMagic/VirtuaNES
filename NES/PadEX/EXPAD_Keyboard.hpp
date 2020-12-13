//////////////////////////////////////////////////////////////////////////
// Family Basic Keyboard                                                //
//////////////////////////////////////////////////////////////////////////
void	EXPAD_Keyboard::Reset()
{
	bGraph = FALSE;
	bOut = FALSE;
	ScanNo = 0;
}

BYTE	EXPAD_Keyboard::Read4016()
{
BYTE	data = 0;

	return	data;
}

BYTE	EXPAD_Keyboard::Read4017()
{
BYTE	data = 0;

	if( ScanNo ) {
		data = 0x1E;
	}

	if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::NEXT ) ) bGraph = TRUE;
	if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::PRIOR) ) bGraph = FALSE;

	switch( ScanNo ) {
		case	1:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F8      ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::RETURN  ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::LBRACKET) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::RBRACKET) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F12      ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::RSHIFT   ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::BACKSLASH)
				 || ConfigWrapper::DirectInputGetm_Sw(Keyboard::YEN      ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::END      ) ) data &= ~0x10;
			}
			break;
		case	2:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F7       ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::AT       ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::COLON    ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::SEMICOLON) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::UNDERLINE ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::SLASH     ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::MINUS     ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::CIRCUMFLEX) ) data &= ~0x10;
			}
			break;
		case	3:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F6) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::O ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::L ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::K ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::PERIOD) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::COMMA ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::P     ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_0    ) ) data &= ~0x10;
			}
			break;
		case	4:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F5) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::I ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::U ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::J ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::M ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::N ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_9) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_8) ) data &= ~0x10;
			}
			break;
		case	5:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F4) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::Y ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::G ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::H ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::B ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::V ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_7) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_6) ) data &= ~0x10;
			}
			break;
		case	6:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F3) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::T ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::R ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::D ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::C ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_5) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_4) ) data &= ~0x10;
			}
			break;
		case	7:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F2) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::W ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::S ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::A ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::X ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::Z ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::E ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_3) ) data &= ~0x10;
			}
			break;
		case	8:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::F1      ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::ESCAPE  ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::Q       ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::LCONTROL)
				 || ConfigWrapper::DirectInputGetm_Sw(Keyboard::RCONTROL) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::LSHIFT) ) data &= ~0x02;
				if( bGraph                       ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_1    ) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::_2    ) ) data &= ~0x10;
			}
			break;
		case	9:
			if( bOut ) {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::HOME ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::UP   ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::RIGHT) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::LEFT ) ) data &= ~0x10;
			} else {
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::DOWN  ) ) data &= ~0x02;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::SPACE ) ) data &= ~0x04;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::DELETE) ) data &= ~0x08;
				if( ConfigWrapper::DirectInputGetm_Sw(Keyboard::INSERT) ) data &= ~0x10;
			}
			break;
		case	10:
			break;
	}

	return	data & 0x1E;
}

void	EXPAD_Keyboard::Write4016( BYTE data )
{
	if( data == 0x05 ) {
		bOut = FALSE;
		ScanNo = 0;
	} else if( data == 0x04 ) {
//		if( ++ScanNo > 9 )
		if( ++ScanNo > 10 )
			ScanNo = 0;
		bOut = !bOut;
	} else if( data == 0x06 ) {
		bOut = !bOut;
	} else {
		ScanNo = 0;
	}
}
