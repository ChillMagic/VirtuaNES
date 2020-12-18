//
// Debug output
//
#ifndef	__DEBUGOUT_INCLUDED__
#define	__DEBUGOUT_INCLUDED__

#include "Base/Typedef.h"

#include <string>
using namespace std;

//typedef	void (__cdecl *DEBUGWINDOWOUTPUT)(LPCTSTR);

class CDebugOut {
public:
	CDebugOut();

	void Clear();

	void Out( LPCSTR fmt, ... );
	void Out( const string& str );

protected:
	void*	hWndDebugOutput; // type: HWND

private:
};

extern	CDebugOut	Dbg;

template <typename... Args>
void DEBUGOUT(Args&&... args) {
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	Dbg.Out(args...);
#endif	// !_DEBUG
}

inline void DEBUGCLR() {
#if	defined(_DEBUG) || defined(_DEBUGOUT)
	Dbg.Clear();
#endif	// !_DEBUG
}

#endif	// !__DEBUGOUT_INCLUDED__

