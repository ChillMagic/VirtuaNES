//
// パスライブラリクラス
//
#ifndef	__CPATHLIB_INCLUDED__
#define	__CPATHLIB_INCLUDED__

#include <string>

#include "Typedef.h"
using namespace std;

class	CPathlib
{
public:
	// パス＋ファイルネームからのパス取得
	static	string	SplitPath( LPCSTR lpszPath );
	// パス＋ファイルネームからのファイル名取得(拡張子なし)
	static	string	SplitFname( LPCSTR lpszPath );
	// パス＋ファイルネームからのファイル名取得(拡張子あり)
	static	string	SplitFnameExt( LPCSTR lpszPath );
	// パス＋ファイルネームからの拡張子取得
	static	string	SplitExt( LPCSTR lpszPath );

	// パス，ファイル名からのパス作成(拡張子あり/なし共用)
	static	string	MakePath( LPCSTR lpszPath, LPCSTR lpszFname );
	// パス，ファイル名，拡張子からのパス作成(拡張子を別に指定)
	static	string	MakePathExt( LPCSTR lpszPath, LPCSTR lpszFname, LPCSTR lpszExt );

	// ベースパスから追加パスの種類を調べてパスを作成する
	// 追加パスが絶対パスならばそのまま，相対パスならばベースパスに追加
	static	string	CreatePath( LPCSTR lpszBasePath, LPCSTR lpszPath );

	// フォルダ選択
	static	BOOL	SelectFolder( void* hWnd, LPCSTR lpszTitle, LPSTR lpszFolder );

protected:
	static INT CALLBACK BffCallback( void* hWnd, UINT uMsg, LPARAM lParam, WPARAM wParam );
private:
};

#endif	// !__CPATHLIB_INCLUDED__

