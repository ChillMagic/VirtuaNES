//
// ムービー情報ダイアログクラス
//
#ifndef	__CMOVIEINFODLG_INCLUDED__
#define	__CMOVIEINFODLG_INCLUDED__

#include "WindowsSDKImport.h"
#include <string>
using namespace std;

#include "Wnd.h"

class	CMovieInfoDlg : public CWnd
{
public:
	// Override from CWnd
	INT	DoModal( HWND hWndParent );

	WORD	m_wRecVersion;
	WORD	m_wVersion;
	DWORD	m_dwFrames;
	DWORD	m_dwRerecordTimes;

protected:
	// Message map
	DLG_MESSAGE_MAP()
	DLGMSG		OnInitDialog( DLGMSGPARAM );
	DLGCMD		OnOK( DLGCMDPARAM );
	DLGCMD		OnCancel( DLGCMDPARAM );
	//
private:
};

#endif	// !__CMOVIEINFODLG_INCLUDED__

