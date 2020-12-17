#pragma once
#include "Base/Typedef.h"

class	CCfgMovie
{
public:
	BYTE	bUsePlayer[4];
	BOOL	bRerecord;
	BOOL	bLoopPlay;
	BOOL	bResetRec;
	BOOL	bPadDisplay;
	BOOL	bTimeDisplay;

	void	Default() {
		bUsePlayer[0] = 0xFF;
		bUsePlayer[1] = 0x00;
		bUsePlayer[2] = 0x00;
		bUsePlayer[3] = 0x00;
		bRerecord = TRUE;
		bLoopPlay = FALSE;
		bResetRec = FALSE;
		bPadDisplay = FALSE;
		bTimeDisplay = FALSE;
	}
};
