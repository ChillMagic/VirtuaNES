//
// Debug output
//
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Base/DebugOut.h"

CDebugOut	Dbg;

static const CHAR szClassName[] = "DebugWindow_wndclass";

CDebugOut::CDebugOut()
{
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	hWndDebugOutput = ::FindWindow( szClassName, NULL );
	if( !hWndDebugOutput ) {
		::OutputDebugString( "DebugWindow がありません\n" );
	}
#endif
}

void CDebugOut::Clear()
{
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	if( hWndDebugOutput ) {
		if( ::IsWindow( (HWND)hWndDebugOutput ) ) {
			::SendMessage((HWND)hWndDebugOutput, WM_APP+1, (WPARAM)NULL, (LPARAM)NULL );
		}
	}
#endif
}

void CDebugOut::Out( LPCSTR fmt, ... )
{
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	CHAR	buf[1000];
	va_list	va;
	va_start( va, fmt );
	::vsprintf( buf, fmt, va );

	if( hWndDebugOutput ) {
		if( ::IsWindow((HWND)hWndDebugOutput ) ) {
			COPYDATASTRUCT	cds;
			cds.dwData = 0;
			cds.lpData = (void*)buf;
			cds.cbData = ::strlen(buf)+1; //  終端のNULLも送る
			//  文字列送信
			::SendMessage((HWND)hWndDebugOutput, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds );
		} else {
			::OutputDebugString( buf );
		}
	} else {
		::OutputDebugString( buf );
	}
#endif
}

void CDebugOut::Out( const string& str )
{
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	Out( (LPSTR)str.c_str() );
#endif
}

