#pragma once
#include "Typedef.h"

class	CCfgEmulator
{
public:
	BOOL	bIllegalOp;
	BOOL	bAutoFrameSkip;
	BOOL	bThrottle;
	INT	nThrottleFPS;
	BOOL	bBackground;
	INT	nPriority;
	BOOL	bFourPlayer;
	BOOL	bCrcCheck;
	BOOL	bDiskThrottle;
	BOOL	bLoadFullscreen;
	BOOL	bPNGsnapshot;
	BOOL	bAutoIPS;

	void	Default() {
		bIllegalOp = FALSE;
		bAutoFrameSkip = TRUE;
		bThrottle = TRUE;
		nThrottleFPS = 120;		// 120FPS
		bBackground = FALSE;
		nPriority = 3;		// Normal
		bFourPlayer = TRUE;		// TRUE:NES FALSE:Famicom
		bCrcCheck = TRUE;
		bDiskThrottle = TRUE;
		bLoadFullscreen = FALSE;
		bPNGsnapshot = FALSE;
		bAutoIPS = FALSE;
	}
};
