//
// 設定保存クラス
//
#ifndef	__CCONFIG_INCLUDED__
#define	__CCONFIG_INCLUDED__

#include <combaseapi.h>
#include <cstdlib>

#include <string>
using namespace std;

#include "ExtSoundFile.h"

#include "Base/Typedef.h"
#include "Base/Macro.h"

class	CCfgGeneral
{
public:
	BOOL	bDoubleExecute;
	BOOL	bStartupLauncher;

	BOOL	bWindowSave;
	BOOL	bWindowZoom;
	RECT	rcWindowPos;

	BOOL	bScreenMode;
	BOOL	nScreenZoom;

	RECT	rcSearchDlgPos;

	RECT	rcPatternViewPos;
	RECT	rcNameTableViewPos;
	RECT	rcPaletteViewPos;
	RECT	rcMemoryViewPos;

	RECT	rcBarcodePos;
	RECT	rcPaletteEditPos;

	BOOL	bNoJoystickID;

	WORD	JoyAxisSetting[16];

	// ジョイパッドの軸の無効化
	//  0 : All enable
	//  1 : X軸以降全て
	//  2 : Y軸以降全て
	//  3 : Z軸以降全て
	//  4 : RX軸以降全て
	//  5 : RY軸以降全て
	//  6 : RZ軸以降全て
	INT	nJoyAxisDisable;

	void	Default() {
		bWindowSave = FALSE;
		bWindowZoom = FALSE;
		rcWindowPos.left = rcWindowPos.right =
		rcWindowPos.top = rcWindowPos.bottom = 0;

		bDoubleExecute = TRUE;
		bStartupLauncher = FALSE;

		bScreenMode = FALSE;
		nScreenZoom = 0;

		rcSearchDlgPos.left = rcSearchDlgPos.right =
		rcSearchDlgPos.top = rcSearchDlgPos.bottom = 0;

		rcPatternViewPos.left = rcPatternViewPos.right =
		rcPatternViewPos.top = rcPatternViewPos.bottom = 0;
		rcNameTableViewPos.left = rcNameTableViewPos.right =
		rcNameTableViewPos.top = rcNameTableViewPos.bottom = 0;
		rcPaletteViewPos.left = rcPaletteViewPos.right =
		rcPaletteViewPos.top = rcPaletteViewPos.bottom = 0;
		rcMemoryViewPos.left = rcMemoryViewPos.right =
		rcMemoryViewPos.top = rcMemoryViewPos.bottom = 0;

		rcBarcodePos.left = rcBarcodePos.right =
		rcBarcodePos.top = rcBarcodePos.bottom = 0;

		rcPaletteEditPos.left = rcPaletteEditPos.right =
		rcPaletteEditPos.top = rcPaletteEditPos.bottom = 0;

		bNoJoystickID = FALSE;
		nJoyAxisDisable = 0;

		for( INT i = 0; i < 16; i++ ) {
			JoyAxisSetting[i] = 0;
		}
	}
};

#include "CCfgPath.h"

#include "CCfgEmulator.h"

#include "CCfgGraphics.h"

#include "CCfgSound.h"

class	CCfgShortCut
{
public:
	WORD	nShortCut[512];

	enum {
		K_ALT   = 0x8000,
		K_CTRL  = 0x4000,
		K_SHIFT = 0x2000,
	};

	void	Default();
};

class	CCfgLanguage
{
public:
	LCID	lcID;
	CHAR	szLanguage[256];

	void	Default() {
		lcID = NULL;
		szLanguage[0] = 0;
	}
};

#include "CCfgController.h"

#include "CCfgMovie.h"

class	CCfgLauncher
{
public:
	RECT	rcWindowPos;

	BYTE	bHeaderView [16];
	BYTE	nHeaderOrder[16];
	SHORT	nHeaderWidth[16];

	BOOL	bActivePause;

	INT	nListSelect;

	BOOL	bSortDir;
	INT	nSortType;

	BYTE	bFolderUse[16];
	CHAR	szFolder[16][_MAX_PATH];

	CHAR	szLastSelect[_MAX_PATH];

	void	Default() {
		rcWindowPos.left = rcWindowPos.right =
		rcWindowPos.top = rcWindowPos.bottom = 0;

		bActivePause = FALSE;

		nListSelect = 0;

		bSortDir = FALSE;
		nSortType = 0;

		INT	i;
		for( i = 0; i < 16; i++ ) {
			bHeaderView [i] = TRUE;
			nHeaderOrder[i] = i;
			nHeaderWidth[i] = (i==0)?160:48;
		}

		for( i = 0; i < 16; i++ ) {
			bFolderUse[i] = FALSE;
			szFolder[i][0] = '\0';
		}

		szLastSelect[0] = '\0';
	}
};

class	CCfgExtraSound
{
public:
	CHAR	szExtSoundFile[ ESF_FILE_MAX ][ MAX_PATH ];

	void	Default() {
		for( INT i = 0; i < ESF_FILE_MAX; i++ ) {
			szExtSoundFile[i][0] = '\0';
		}
	}
};

class	CCfgNetPlay
{
public:
	RECT	rcChatPos;

	INT	nRecentPort, nRecentHost;
	CHAR	szRecentPort[16][_MAX_PATH+1];
	CHAR	szRecentHost[16][_MAX_PATH+1];
	CHAR	szNick[_MAX_PATH+1];

	void	Default();
};

class	CConfig
{
public:
	CConfig() {
		m_bKeyboardDisable = FALSE;
		Default();
	}

	CCfgGeneral	general;
	CCfgPath	path;
	CCfgEmulator	emulator;
	CCfgGraphics	graphics;
	CCfgSound	sound;
	CCfgShortCut	shortcut;
	CCfgLanguage	language;
	CCfgController	controller;
	CCfgMovie	movie;
	CCfgLauncher	launcher;
	CCfgExtraSound	extsound;
	CCfgNetPlay	netplay;

	void	Default() {
		general.Default();
		path.Default();
		emulator.Default();
		graphics.Default();
		sound.Default();
		shortcut.Default();
		language.Default();
		controller.Default();
		movie.Default();
		launcher.Default();
		extsound.Default();
		netplay.Default();
	}

	void	Load();
	void	Save();

// Checker
	void	InputKeyboardDisable( BOOL bEnable ) {
		m_bKeyboardDisable = bEnable;
	}

	BOOL	ButtonCheck( INT nNo, INT nID );
	BOOL	ExButtonCheck( INT nNo, INT nID );
	BOOL	NsfButtonCheck( INT nID );
	BOOL	ButtonCheck( INT nID, WORD* pKey );

// Converter
	string	ShortcutToKeyName( INT nShortcut );

// Table
	static	INT	SamplingRateTable[];
	static	INT	ShortcutKeyID[];
protected:

	BOOL	m_bKeyboardDisable;
private:
};

#include "CGameOption.h"

extern	CConfig		Config;
extern	CGameOption	GameOption;

#endif // !__CCONFIG_INCLUDED__
