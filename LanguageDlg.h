//
// ランゲージダイアログクラス
//
#ifndef	__CLANGUAGEDLG_INCLUDED__
#define	__CLANGUAGEDLG_INCLUDED__

#include "WindowsSDKImport.h"
#include <string>
using namespace std;

#include "Wnd.h"

class	CLanguageDlg : public CWnd
{
public:
	// Override from CWnd
	INT	DoModal( HWND hWndParent );
protected:
	// Message map
	DLG_MESSAGE_MAP()
	DLGMSG		OnInitDialog( DLGMSGPARAM );
	DLGCMD		OnOK( DLGCMDPARAM );
	DLGCMD		OnCancel( DLGCMDPARAM );
	DLGCMD		OnDefault( DLGCMDPARAM );
	//

	INT	m_nPluginID;
private:
};

#endif	// !__CLANGUAGEDLG_INCLUDED__

