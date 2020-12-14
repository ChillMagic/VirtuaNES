#pragma once
#include "Typedef.h"
#include <cstdlib>

class	CCfgGraphics
{
public:
	BOOL	bAspect;
	BOOL	bAllSprite;
	BOOL	bAllLine;
	BOOL	bFPSDisp;
	BOOL	bTVFrame;
	BOOL	bScanline;
	INT	nScanlineColor;
	BOOL	bSyncDraw;
	BOOL	bFitZoom;

	BOOL	bLeftClip;

	BOOL	bWindowVSync;

	BOOL	bSyncNoSleep;

	BOOL	bDiskAccessLamp;

	BOOL	bDoubleSize;
	BOOL	bSystemMemory;
	BOOL	bUseHEL;

	BOOL	bNoSquareList;

	INT	nGraphicsFilter;

	DWORD	dwDisplayWidth;
	DWORD	dwDisplayHeight;
	DWORD	dwDisplayDepth;
	DWORD	dwDisplayRate;

	BOOL	bPaletteFile;
	CHAR	szPaletteFile[MAX_PATH];

	void	Default() {
		bAspect = FALSE;
		bAllSprite = TRUE;
		bAllLine = FALSE;
		bFPSDisp = FALSE;
		bTVFrame = FALSE;
		bScanline = FALSE;
		nScanlineColor = 75;
		bSyncDraw = FALSE;
		bFitZoom = FALSE;

		bLeftClip = TRUE;

		bWindowVSync = FALSE;
		bSyncNoSleep = FALSE;

		bDiskAccessLamp = FALSE;

		bDoubleSize = FALSE;
		bSystemMemory = FALSE;
		bUseHEL = FALSE;

		bNoSquareList = FALSE;

		nGraphicsFilter = 0;

		dwDisplayWidth = 640;
		dwDisplayHeight = 480;
		dwDisplayDepth = 16;
		dwDisplayRate = 0;

		bPaletteFile = FALSE;
		szPaletteFile[0] = 0;
	}
};
