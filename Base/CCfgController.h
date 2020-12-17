#pragma once
#include "Base/Typedef.h"

class	CCfgController
{
public:
	WORD	nButton[4][64];
	WORD	nRapid [4][ 2];
	// 0:Crazy Climber
	// 1:Famly Trainer
	// 2:Exciting Boxing
	// 3:Mahjang
	WORD	nExButton[4][64];
	WORD	nNsfButton[64];
	WORD	nVSUnisystem[64];

	void	Default() {
		DefaultController1();
		DefaultController2();
		DefaultController3();
		DefaultController4();
		DefaultExController0();
		DefaultExController1();
		DefaultExController2();
		DefaultExController3();
		DefaultNsfController();
		DefaultVSUnisystem();
	}

	void	DefaultController1();

	void	DefaultController2();

	void	DefaultController3() {
		for( INT i = 0; i < 64; i++ )
			nButton[2][i] = 0;

		nRapid[2][0] = 0;	// A Rapid speed
		nRapid[2][1] = 0;	// B Rapid speed
	}

	void	DefaultController4() {
		for( INT i = 0; i < 64; i++ )
			nButton[3][i] = 0;

		nRapid[3][0] = 0;	// A Rapid speed
		nRapid[3][1] = 0;	// B Rapid speed
	}

	void	DefaultExController0() {
		// Crazy Climberｺﾝﾄﾛｰﾗ(実際には存在しない)
		for( INT i = 0; i < 64; i++ )
			nExButton[0][i] = 0;
//		nExButton[0][ 0] = 0;	// L up
//		nExButton[0][ 1] = 0;	// L down
//		nExButton[0][ 2] = 0;	// L left
//		nExButton[0][ 3] = 0;	// L right
//		nExButton[0][ 4] = 0;	// R up
//		nExButton[0][ 5] = 0;	// R down
//		nExButton[0][ 6] = 0;	// R left
//		nExButton[0][ 7] = 0;	// R right
	}

	void	DefaultExController1() {
		// Famly Trainerｺﾝﾄﾛｰﾗ
		for( INT i = 0; i < 64; i++ )
			nExButton[1][i] = 0;
	}

	void	DefaultExController2() {
		// Exciting Boxingｺﾝﾄﾛｰﾗ
		for( INT i = 0; i < 64; i++ )
			nExButton[2][i] = 0;
	}

	void	DefaultExController3() {
		// Mahjangｺﾝﾄﾛｰﾗ
		for( INT i = 0; i < 64; i++ )
			nExButton[3][i] = 0;
	}

	void	DefaultNsfController();

	void	DefaultVSUnisystem();
};
