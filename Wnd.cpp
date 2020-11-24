//
// �ւȂ��傱�E�C���h�E�N���X
//
#include "DebugOut.h"
#include "Wnd.h"

// Instance
CWndList	WndList;

list<CWnd*>	CWndList::m_WndPtrList;

// �D�L���c
CWndList::CWndList()
{
//	m_WndPtrList.clear();
}

CWndList::~CWndList()
{
//	if( !m_WndPtrList.empty() )
//		m_WndPtrList.clear();
}

void	CWndList::Add( CWnd* pWnd )
{
	m_WndPtrList.push_back( pWnd );
}

void	CWndList::Del( CWnd* pWnd )
{
	for( list<CWnd*>::iterator it=m_WndPtrList.begin(); it!=m_WndPtrList.end(); ) {
		if( *it == pWnd ) {
			m_WndPtrList.erase(it);
			break;
		} else {
			++it;
		}
	}
}

BOOL	CWndList::IsDialogMessage( LPMSG msg )
{
	if( m_WndPtrList.empty() )
		return	FALSE;

	list<CWnd*>::iterator it=m_WndPtrList.begin();
	while( it != m_WndPtrList.end() ) {
		if( ::IsDialogMessage( (*it)->m_hWnd, msg ) )
			return	TRUE;
		++it;
	}

	return	FALSE;
}

CWnd::CWnd()
{
	m_hWnd = NULL;
	m_hMenu = NULL;
}

CWnd::~CWnd()
{
}

void	CWnd::SetThis()
{
	// Dispatch�o����悤��CWnd*�𖄂ߍ���
	if( m_hWnd ) {
		::SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
	}
}

LRESULT	CALLBACK CWnd::g_WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// �E�C���h�E���J���O�ɂ������菈������
	if( msg == WM_CREATE ) {
		LPCREATESTRUCT	lpcs = (LPCREATESTRUCT)lParam;
		CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );
		if( !pWnd ) {
			// CWnd* this�𖄂ߍ���
			::SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpcs->lpCreateParams );
			// �����̃E�C���h�E�n���h��
			pWnd = (CWnd*)lpcs->lpCreateParams;
			pWnd->m_hWnd = hWnd;
		}
	}
	// CWnd* this�𖄂ߍ���ł���
	CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

	if( pWnd ) {
		return	pWnd->DispatchWnd( hWnd, msg, wParam, lParam );
	} else {
		return	::DefWindowProc(  hWnd, msg, wParam, lParam );
	}
}

BOOL	CALLBACK CWnd::g_DlgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// �f�B�X�p�b�`�O�ɂ������菈������
	if( msg == WM_INITDIALOG ) {
		// Dispatch�o����悤��CWnd*�𖄂ߍ���(���[�_���͕K��DialogBoxParam�ŋN�����鎖)
		// CWnd* this�𖄂ߍ���ł��邪�C���[�_���ł͓����Ă��Ȃ�
		CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

		if( !pWnd ) {
			::SetWindowLong( hWnd, GWL_USERDATA, (LONG)lParam );
			pWnd = (CWnd*)lParam;
		}
		// �����̃E�C���h�E�n���h��
		pWnd->m_hWnd = hWnd;

		// �_�C�A���O�𒆉��Ɉړ�����:)
		HWND hWndParent = ::GetParent( hWnd );
		if( hWndParent ) {
			RECT	rcParent, rc;
			::GetWindowRect( hWndParent, &rcParent );
			::GetWindowRect( hWnd, &rc );
			INT x = rcParent.left+(rcParent.right-rcParent.left)/2-(rc.right-rc.left)/2;
			INT y = rcParent.top +(rcParent.bottom-rcParent.top)/2-(rc.bottom-rc.top)/2;
//			DEBUGOUT( "X=%d  Y=%d\n", x, y );
			::SetWindowPos( hWnd, NULL, x, y, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
		}
	}

	// CWnd* this�𖄂ߍ���ł���
	CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

	if( pWnd ) {
		return	pWnd->DispatchDlg( hWnd, msg, wParam, lParam );
	} else {
		return	FALSE;
	}
}

