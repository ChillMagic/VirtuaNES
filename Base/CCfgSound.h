#pragma once
#include "Base/Typedef.h"

class	CCfgSound
{
public:
	BOOL	bEnable;
	INT	nRate;
	INT	nBits;
	INT	nBufferSize;

	INT	nFilterType;

	BOOL	bChangeTone;

	BOOL	bDisableVolumeEffect;
	BOOL	bExtraSoundEnable;

	//  0:Master
	//  1:Rectangle 1
	//  2:Rectangle 2
	//  3:Triangle
	//  4:Noise
	//  5:DPCM
	//  6:VRC6
	//  7:VRC7
	//  8:FDS
	//  9:MMC5
	// 10:N106
	// 11:FME7
	SHORT	nVolume[16];

	void	Default() {
		bEnable		= TRUE;
		nRate		= 22050;
		nBits		= 8;
		nBufferSize	= 4;

		nFilterType	= 0;

		bChangeTone	= FALSE;

		bDisableVolumeEffect = FALSE;
		bExtraSoundEnable = TRUE;

		for( INT i = 0; i < 16; i++ ) {
			nVolume[i] = 100;
		}
	}
};
