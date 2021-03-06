﻿#ifndef	__VSUNISYSTEM_INCLUDED__
#define	__VSUNISYSTEM_INCLUDED__

#include <cstdio>
#include <cstdlib>

#include "Base/Typedef.h"

struct VSDIPSWITCH
{
	LPCSTR	name;
	WORD	value;
};

extern	VSDIPSWITCH	vsdip_default[];

extern	VSDIPSWITCH*	FindVSDipSwitchTable( DWORD crc );
extern	BYTE	GetVSDefaultDipSwitchValue( DWORD crc );

#endif	// !__VSUNISYSTEM_INCLUDED__
