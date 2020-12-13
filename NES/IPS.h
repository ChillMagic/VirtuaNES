#ifndef	__IPS_INCLUDED__
#define	__IPS_INCLUDED__

#define	WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Typedef.h"
#include "Macro.h"

BOOL	ApplyIPS( const char* filename, LPBYTE pROM, LONG imagesize );

#endif	// !__IPS_INCLUDED__
