
#include "ConfigWrapper.h"
#include "Config.h"

CCfgGraphics& ConfigWrapper::GetCCfgGraphics()
{
	return Config.graphics;
}

CCfgSound& ConfigWrapper::GetCCfgSound()
{
	return Config.sound;
}

CCfgController& ConfigWrapper::GetCCfgController()
{
	return Config.controller;
}

CCfgMovie& ConfigWrapper::GetCCfgMovie()
{
	return Config.movie;
}

CCfgPath& ConfigWrapper::GetCCfgPath()
{
	return Config.path;
}

CCfgEmulator& ConfigWrapper::GetCCfgEmulator()
{
	return Config.emulator;
}

CGameOption& ConfigWrapper::GetCGameOption()
{
	return GameOption;
}


BOOL ConfigWrapper::ButtonCheck(INT nNo, INT nID)
{
	return Config.ButtonCheck(nNo, nID);
}
BOOL ConfigWrapper::ExButtonCheck(INT nNo, INT nID)
{
	return Config.ExButtonCheck(nNo, nID);
}
BOOL ConfigWrapper::NsfButtonCheck(INT nID)
{
	return Config.NsfButtonCheck(nID);
}
BOOL ConfigWrapper::ButtonCheck(INT nID, WORD* pKey)
{
	return Config.ButtonCheck(nID, pKey);
}
