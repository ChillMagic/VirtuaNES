#ifndef	__VSUNISYSTEM_INCLUDED__
#define	__VSUNISYSTEM_INCLUDED__

#define	WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdio>
#include <cstdlib>

#include "Typedef.h"

struct VSDIPSWITCH
{
	LPCSTR	name;
	WORD	value;
};

extern	VSDIPSWITCH	vsdip_default[];

extern	VSDIPSWITCH*	FindVSDipSwitchTable( DWORD crc );
extern	BYTE	GetVSDefaultDipSwitchValue( DWORD crc );

#endif	// !__VSUNISYSTEM_INCLUDED__
