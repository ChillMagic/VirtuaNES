//
// �`���b�g�_�C�A���O�N���X
//
#ifndef	__CCHATDLG_INCLUDED__
#define	__CCHATDLG_INCLUDED__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
using namespace std;

#include "Wnd.h"

class	CChatDlg : public CWnd
{
public:
	// Override from CWnd
	BOOL	Create( HWND hWndParent );
	void	Destroy();

	// Set Message
	void	SetEditText();
protected:
	// Message map
	DLG_MESSAGE_MAP()
	DLGMSG		OnInitDialog( DLGMSGPARAM );
	DLGMSG		OnDestroy( DLGMSGPARAM );
	DLGMSG		OnClose( DLGMSGPARAM );
	DLGMSG		OnActivate( DLGMSGPARAM );
	DLGMSG		OnSetCursor( DLGMSGPARAM );
	DLGMSG		OnSize( DLGMSGPARAM );

	DLGMSG		OnControlColorStatic( DLGMSGPARAM );

	DLGMSG		OnCopyData( DLGMSGPARAM );

	DLGCMD		OnMessageFocus( DLGCMDPARAM );

	DLGCMD		OnOK( DLGCMDPARAM );
	DLGCMD		OnCancel( DLGCMDPARAM );
	DLGCMD		OnSend( DLGCMDPARAM );
	//

	// �ʒu
	RECT		m_rcClient;	// �N���C�A���g�G���A
	RECT		m_rcMessage;	// ���b�Z�[�W�g
	RECT		m_rcEdit;	// �G�f�B�b�g�g
	RECT		m_rcButton;	// ���M�{�^��

private:
};

#endif	// !__CCHATDLG_INCLUDED__

