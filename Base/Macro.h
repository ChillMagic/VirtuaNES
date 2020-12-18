//
// 便利かも知れないマクロたち
//
#ifndef __MACRO_INCLUDED__
#define __MACRO_INCLUDED__

#include <cstring>

// 多重呼び出し対応マクロちゃん
template <typename T> void DELETEPTR(T &x) { if (x) { delete x; x = NULL; } }
template <typename T> void DELETEARR(T &x) { if (x) { delete[] x; x = NULL; } }
template <typename T> void RELEASE(T &x) { if(x) { x->Release(); x = NULL; } }
template <typename T> void FREE(T &x) { if(x) { free(x); x = NULL; } }
template <typename T> void FCLOSE(T &x) { if(x) { fclose(x); x = NULL; }}
template <typename T> void GDIDELETE(T &x) { if(x) { ::DeleteObject(x); x = NULL; }}
template <typename T> void CLOSEHANDLE(T &x) { if(x) { ::CloseHandle(x); x = NULL; }}

// その他
template <typename T1, typename T2>
void ZEROMEMORY(T1 p, T2 s) { std::memset(p, 0, s); }

#ifndef ZeroMemory
template <typename T1, typename T2>
void ZeroMemory(T1 Destination, T2 Length) {
	std::memset((Destination), 0, (Length));
}
template <typename T1, typename T2, typename T3>
void FillMemory(T1 Destination, T2 Length, T3 Fill) {
	std::memset((Destination), (Fill), (Length));
}
#endif

// RECT構造体用
template <typename T> auto RCWIDTH(T rc) { return rc.right - rc.left; }
template <typename T> auto RCHEIGHT(T rc) { return rc.bottom - rc.top; }

#endif // !__MACRO_INCLUDED__
