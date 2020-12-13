#define	WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "VirtuaNESres.h"

BOOL WINAPI DllMain( HINSTANCE hInstanceDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	return	TRUE;
}

INT	GetVlpVersion( void )
{
	return	VIRTUANES_PLUGIN_VERSION;
}

void	GetVlpLanguage( LPSTR lpLanguege )
{
	strcpy( lpLanguege, "Japanese" );
}

LCID	GetVlpLocaleID( void )
{
	return	0x411;
}

