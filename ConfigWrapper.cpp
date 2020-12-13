
#include "ConfigWrapper.h"
#include "Config.h"
#include "DirectDraw.h"
#include "DirectInput.h"
#include "DirectSound.h"

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


void ConfigWrapper::DirectDrawSetMessageString(LPCSTR str)
{
	DirectDraw.SetMessageString(str);
}
void ConfigWrapper::DirectDrawSetZapperMode(BOOL bZapper)
{
	DirectDraw.SetZapperMode(bZapper);
}
void ConfigWrapper::DirectDrawSetZapperDrawMode(BOOL bDraw)
{
	DirectDraw.SetZapperDrawMode(bDraw);
}
BYTE ConfigWrapper::DirectDrawGetZapperHit()
{
	return DirectDraw.GetZapperHit();
}
void ConfigWrapper::DirectDrawSetZapperPos(LONG x, LONG y)
{
	DirectDraw.SetZapperPos(x, y);
}

void ConfigWrapper::DirectDrawGetPaletteData(RGBQUAD* rgb)
{
	DirectDraw.GetPaletteData((::RGBQUAD*)rgb);
}

BYTE ConfigWrapper::DirectInputGetm_Sw(Keyboard key)
{
	return DirectInput.m_Sw[key];
}

BOOL ConfigWrapper::DirectSoundEsfPlay(INT no)
{
	return DirectSound.EsfPlay(no);
}

BOOL ConfigWrapper::DirectSoundEsfPlayLoop(INT no)
{
	return DirectSound.EsfPlayLoop(no);
}

BOOL ConfigWrapper::DirectSoundEsfStop(INT no)
{
	return DirectSound.EsfStop(no);
}

void ConfigWrapper::DirectSoundEsfAllStop()
{
	DirectSound.EsfAllStop();
}
