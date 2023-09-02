﻿//
// Recent File クラス
//
#ifndef	__CRECENT_INCLUDED__
#define	__CRECENT_INCLUDED__

#include "WindowsSDKImport.h"
#include <cstdio>
#include <cstdlib>

#include <string>
using namespace std;

#include "Pathlib.h"
#include "Registry.h"

class	CRecent
{
public:
	static	LPCSTR	GetName( INT nID );
	static	LPCSTR	GetPath( INT nID );

	static	void	UpdateMenu( HMENU hMenu );
	static	void	Add( LPCSTR lpszPath );

	static	void	Load();
	static	void	Save();

protected:
	enum { RECENT_MAX=10 };
	static	CHAR	m_RecentName[RECENT_MAX][_MAX_PATH];
	static	CHAR	m_RecentPath[RECENT_MAX][_MAX_PATH];
	static	CHAR	m_TempPath[_MAX_PATH];

	// Helper
	static	void	MakeManuPath( LPSTR lpszPath );
private:
};

#endif	// !__CRECENT_INCLUDED__

