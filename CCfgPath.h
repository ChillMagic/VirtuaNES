#pragma once
#include "Typedef.h"
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

	CHAR	szRomPath[_MAX_PATH];
	CHAR	szSavePath[_MAX_PATH];
	CHAR	szStatePath[_MAX_PATH];
	CHAR	szSnapshotPath[_MAX_PATH];
	CHAR	szMoviePath[_MAX_PATH];
	CHAR	szWavePath[_MAX_PATH];
	CHAR	szCheatPath[_MAX_PATH];
	CHAR	szIpsPath[_MAX_PATH];

	void	Default();
};
