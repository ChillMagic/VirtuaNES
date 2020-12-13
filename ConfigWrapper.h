#pragma once
#include "CCfgGraphics.h"
#include "CCfgSound.h"
#include "CCfgController.h"
#include "CCfgPath.h"
#include "CCfgEmulator.h"
#include "CCfgMovie.h"
#include "CGameOption.h"

class ConfigWrapper {
public:
	static CCfgGraphics& GetCCfgGraphics();
	static CCfgSound& GetCCfgSound();
	static CCfgController& GetCCfgController();
	static CCfgMovie& GetCCfgMovie();
	static CCfgPath& GetCCfgPath();
	static CCfgEmulator& GetCCfgEmulator();
	static CGameOption& GetCGameOption();

	static BOOL ButtonCheck(INT nNo, INT nID);
	static BOOL ExButtonCheck(INT nNo, INT nID);
	static BOOL NsfButtonCheck(INT nID);
	static BOOL ButtonCheck(INT nID, WORD* pKey);
};
