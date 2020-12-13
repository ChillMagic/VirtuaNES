//
// レジストリサポートクラス
//
#ifndef	__CREGISTRY_INCLUDED__
#define	__CREGISTRY_INCLUDED__

#include "Typedef.h"

#include <string>
using namespace std;

class	CRegistry
{
public:
	static	void	SetRegistryKey( LPCSTR	lpszKey );

#ifdef GetProfileInt
#undef GetProfileInt
#undef GetProfileString
#undef WriteProfileString
#endif
	static	UINT	GetProfileInt   ( LPCSTR lpszSection, LPCSTR lpszEntry, INT nDefault );
	static	BOOL	GetProfileString( LPCSTR lpszSection, LPCSTR lpszEntry, LPVOID lpData, UINT nBytes );
	static	BOOL	GetProfileBinary( LPCSTR lpszSection, LPCSTR lpszEntry, LPVOID lpData, UINT nBytes );

	static	BOOL	WriteProfileInt( LPCSTR lpszSection, LPCSTR lpszEntry, INT nValue );
	static	BOOL	WriteProfileString( LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue );
	static	BOOL	WriteProfileBinary( LPCSTR lpszSection, LPCSTR lpszEntry, LPVOID pData, UINT nBytes );
};

#endif	// !__CREGISTRY_INCLUDED__
