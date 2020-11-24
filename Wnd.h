//
// �ւȂ��傱�E�C���h�E�N���X
//
// �p�����Ȃ��ƈӖ�������^^;
//
#ifndef	__CWND_INCLUDED__
#define	__CWND_INCLUDED__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <string>
#include <list>
using namespace std;

// prototype
class	CWnd;

// ���[�h���X������������ׂ̃C���`�L�N���X
class	CWndList
{
public:
	CWndList();
	~CWndList();

	static	void	Add( CWnd* pWnd );	// ���X�g�ɉ�����
	static	void	Del( CWnd* pWnd );	// ���X�g����폜����

	static	BOOL	IsDialogMessage( LPMSG msg );
protected:
private:
	static	list<CWnd*>	m_WndPtrList;
};

// ���ʂ̃E�C���h�E
class	CWnd
{
public:
	CWnd();
	virtual	~CWnd();

	HWND	m_hWnd;
	HMENU	m_hMenu;

	// Override
	virtual	BOOL	Create( HWND hWndParent ) { return FALSE; };
	virtual	void	Destroy() {};

	// Override for ModalDialog
	virtual	INT	DoModal( HWND hWndParent ) { return 0; }

	// For message filtering
	virtual	BOOL	PreTranslateMessage( MSG* pMsg ) { return FALSE; }
protected:
	void	SetThis();

	// Static
	static	LRESULT	CALLBACK g_WndProc(  HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	static	BOOL	CALLBACK g_DlgProc(  HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	// Override
	virtual	LRESULT	DispatchWnd( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{ return ::DefWindowProc(  hWnd, msg, wParam, lParam ); }

	virtual	BOOL	DispatchDlg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{ return FALSE; }
private:
};

// �E�C���h�E���b�Z�[�W�p
// �N���X��`�}�N��
#define	WND_MESSAGE_MAP()	HRESULT DispatchWnd( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

#define	WNDMSG			BOOL
#define	WNDCMD			void
#define	WNDNOTIFY		void

#define	WNDMSGPARAM		HWND hWnd, WPARAM wParam, LPARAM lParam, HRESULT& hResult
#define	WNDCMDPARAM		HWND hWnd, UINT uID
#define	WNDNOTIFYPARAM		HWND hWnd, UINT uID, NMHDR* pNMHDR, LRESULT& hResult

// �C���v�������g�}�N��
#define	WND_MESSAGE_BEGIN(cls)	\
	HRESULT cls::DispatchWnd( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {\
		HRESULT	hResult = 0L;\
		switch( msg ) {
#define	WND_ON_MESSAGE(msg,fnc)	\
	case (msg): {\
		if( fnc( hWnd, wParam, lParam, hResult ) )\
			return	hResult;\
	}\
	break;
// �R�}���h��COMMAND_BEGIN() �` COMMAND_END()�̒��ɋL�q����(�P�Ȃ�if�Ȃ̂�(^^;)
#define	WND_COMMAND_BEGIN() \
	case	WM_COMMAND: {
#define	WND_ON_COMMAND(id,fnc) \
	if( LOWORD(wParam) == (id) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	WND_ON_COMMAND_RANGE(id,idend,fnc) \
	if( LOWORD(wParam) >= (id) && LOWORD(wParam) <= (idend) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
// Notify commands
#define	WND_ON_COMMAND_NOTIFY(id,nfy,fnc) \
	if( LOWORD(wParam) == (id) && HIWORD(wParam) == (nfy) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	WND_ON_COMMAND_NOTIFY_RANGE(id,idend,nfy,fnc) \
	if( LOWORD(wParam) >= (id) && LOWORD(wParam) <= (idend) && HIWORD(wParam) == (nfy) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	WND_COMMAND_END() \
	return	0L; }; break;

// WM_NOTIFY��NOTIFY_BEGIN() �` NOTIFY_END()�̒��ɋL�q����(�P�Ȃ�if�Ȃ̂�^^;)
#define	WND_NOTIFY_BEGIN() \
	case	WM_NOTIFY: { \
		LRESULT	hResult = 0L;
#define	WND_ON_NOTIFY(id,msg,fnc) \
	if( (UINT)wParam == (id) && ((NMHDR*)lParam)->code == (msg) ) {\
		fnc( ((NMHDR*)lParam)->hwndFrom, (UINT)wParam, (NMHDR*)lParam, hResult );\
		return	(BOOL)hResult; }
#define	WND_ON_NOTIFY_RANGE(id,idend,msg,fnc) \
	if( (UINT)wParam >= (id) && (UINT)wParam <= (idend) && ((NMHDR*)lParam)->code == (msg) ) {\
		fnc( ((NMHDR*)lParam)->hwndFrom, (UINT)wParam, (NMHDR*)lParam, hResult );\
		return	(BOOL)hResult; }
#define	WND_NOTIFY_END() \
	return	FALSE; }; break;

#define	WND_MESSAGE_END() \
	default: break; }\
	return	::DefWindowProc( hWnd, msg, wParam, lParam );\
	}

// �_�C�A���O���b�Z�[�W�p
// �N���X��`�}�N��
#define	DLG_MESSAGE_MAP()	BOOL DispatchDlg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

#define	DLGMSG			BOOL
#define	DLGCMD			void
#define	DLGNOTIFY		void

#define	DLGMSGPARAM		HWND hWnd, WPARAM wParam, LPARAM lParam, BOOL& bResult
#define	DLGCMDPARAM		HWND hWnd, UINT uID
#define	DLGNOTIFYPARAM		HWND hWnd, UINT uID, NMHDR* pNMHDR, LRESULT& hResult

// �C���v�������g�}�N��
#define	DLG_MESSAGE_BEGIN(cls)	\
	BOOL cls::DispatchDlg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {\
		BOOL	bResult = TRUE;\
		switch( msg ) {
#define	DLG_ON_MESSAGE(msg,fnc)	\
	case (msg): {\
		if( fnc( hWnd, wParam, lParam, bResult ) )\
			return	bResult;\
	}\
	break;
// �R�}���h��COMMAND_BEGIN() �` COMMAND_END()�̒��ɋL�q����(�P�Ȃ�if�Ȃ̂�^^;)
#define	DLG_COMMAND_BEGIN() \
	case	WM_COMMAND: {
#define	DLG_ON_COMMAND(id,fnc) \
	if( LOWORD(wParam) == (id) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	DLG_ON_COMMAND_RANGE(id,idend,fnc) \
	if( LOWORD(wParam) >= (id) && LOWORD(wParam) <= (idend) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
// Notify commands
#define	DLG_ON_COMMAND_NOTIFY(id,nfy,fnc) \
	if( LOWORD(wParam) == (id) && HIWORD(wParam) == (nfy) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	DLG_ON_COMMAND_NOTIFY_RANGE(id,idend,nfy,fnc) \
	if( LOWORD(wParam) >= (id) && LOWORD(wParam) <= (idend) && HIWORD(wParam) == (nfy) ) \
		fnc( (HWND)lParam, LOWORD(wParam) );
#define	DLG_COMMAND_END() \
	return	FALSE; }; break;

// WM_NOTIFY��NOTIFY_BEGIN() �` NOTIFY_END()�̒��ɋL�q����(�P�Ȃ�if�Ȃ̂�^^;)
#define	DLG_NOTIFY_BEGIN() \
	case	WM_NOTIFY: { \
		LRESULT	hResult = 0L;
#define	DLG_ON_NOTIFY(id,msg,fnc) \
	if( (UINT)wParam == (id) && ((NMHDR*)lParam)->code == (msg) ) {\
		fnc( ((NMHDR*)lParam)->hwndFrom, (UINT)wParam, (NMHDR*)lParam, hResult );\
		return	(BOOL)hResult; }
#define	DLG_ON_NOTIFY_RANGE(id,idend,msg,fnc) \
	if( (UINT)wParam >= (id) && (UINT)wParam <= (idend) && ((NMHDR*)lParam)->code == (msg) ) {\
		fnc( ((NMHDR*)lParam)->hwndFrom, (UINT)wParam, (NMHDR*)lParam, hResult );\
		return	(BOOL)hResult; }
#define	DLG_NOTIFY_END() \
	return	FALSE; }; break;

#define	DLG_MESSAGE_END() \
	default: break; }\
	return	FALSE;\
	}

//
// �_�C�A���O���R���g���[���w���p�[�}�N��
//
#define	BTNCHECK(ctrlid,check)	::CheckDlgButton(m_hWnd,(ctrlid),(check)?BST_CHECKED:BST_UNCHECKED)
#define	IsBTNCHECK(ctrlid)	((::IsDlgButtonChecked(m_hWnd,(ctrlid))==BST_CHECKED)?TRUE:FALSE)

#define	CTRLENABLE(ctrlid,enable) ::EnableWindow(::GetDlgItem(m_hWnd,(ctrlid)),enable);

#endif	// !__CWND_INCLUDED__
