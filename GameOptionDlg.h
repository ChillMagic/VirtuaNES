//
// ゲームオプションダイアログクラス
//
#ifndef	__CGAMEOPTIONDLG_INCLUDED__
#define	__CGAMEOPTIONDLG_INCLUDED__

#include "WindowsSDKImport.h"
#include <string>
using namespace std;

#include "Wnd.h"
#include "Config.h"

class	CGameOptionDlg : public CWnd
{
public:
	// Override from CWnd
	INT	DoModal( HWND hWndParent );

protected:
	void	OnInitialMember();

	// Message map
	DLG_MESSAGE_MAP()
	DLGMSG		OnInitDialog( DLGMSGPARAM );
	DLGCMD		OnOK( DLGCMDPARAM );
	DLGCMD		OnCancel( DLGCMDPARAM );
	DLGCMD		OnDefault( DLGCMDPARAM );
	DLGCMD		OnNotSave( DLGCMDPARAM );
	//
private:
};

#endif	// !__CGAMEOPTIONDLG_INCLUDED__

