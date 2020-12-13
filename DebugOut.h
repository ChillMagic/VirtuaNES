//
// Debug output
//
#ifndef	__DEBUGOUT_INCLUDED__
#define	__DEBUGOUT_INCLUDED__

#include "Typedef.h"

#include <string>
using namespace std;

typedef	void (__cdecl *DEBUGWINDOWOUTPUT)(LPCTSTR);

class CDebugOut {
public:
	CDebugOut();

	void Clear();

	void __cdecl Out( LPCSTR fmt, ... );
	void Out( const string& str );

protected:
	void*	hWndDebugOutput; // type: HWND

private:
};

extern	CDebugOut	Dbg;

#if	defined(_DEBUG) || defined(_DEBUGOUT)
#define	DEBUGOUT	Dbg.Out
#else
#define	DEBUGOUT
#endif	// !_DEBUG

#if	defined(_DEBUG) || defined(_DEBUGOUT)
#define	DEBUGCLR	Dbg.Clear
#else
#define	DEBUGCLR
#endif	// !_DEBUG

#endif	// !__DEBUGOUT_INCLUDED__

