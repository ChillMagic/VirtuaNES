#pragma once
#include "Base/Typedef.h"
#include <cstdlib>

class	CCfgPath
{
public:
	BOOL	bRomPath;
	BOOL	bSavePath;
	BOOL	bStatePath;
	BOOL	bSnapshotPath;
	BOOL	bMoviePath;
	BOOL	bWavePath;
	BOOL	bCheatPath;
	BOOL	bIpsPath;

	CHAR	szRomPath[MAX_PATH];
	CHAR	szSavePath[MAX_PATH];
	CHAR	szStatePath[MAX_PATH];
	CHAR	szSnapshotPath[MAX_PATH];
	CHAR	szMoviePath[MAX_PATH];
	CHAR	szWavePath[MAX_PATH];
	CHAR	szCheatPath[MAX_PATH];
	CHAR	szIpsPath[MAX_PATH];

	void	Default();
};
