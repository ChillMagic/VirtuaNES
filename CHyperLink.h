#ifndef	__CHYPERLINK_INCLUDED__
#define	__CHYPERLINK_INCLUDED__

//
// �X�^�e�B�b�N�R���g���[����Subclass�����ăn�C�p�[�����N���T�|�[�g
//
// Usage: CHyperLink	hyperlink;
// hyperlink.Attach( GetDlgItem( hWnd, IDC_URL ) );
//
class	CHyperLink
{
public:
	CHyperLink() : m_hWnd(NULL), m_lpLabel(NULL), 
			m_hCursor(NULL), m_hFont(NULL),
			m_lpHyperLink(NULL), m_lpfnOldWndProc(NULL)
	{
	}
	~CHyperLink()
	{
		Detach();
	}

	// �R���g���[���ɃA�^�b�`����
	BOOL	Attach( HWND hWnd, LPCSTR lpLabel = NULL, LPCSTR lpHyperLink = NULL )
	{
		if( m_hWnd )
			return	FALSE;	// ����Attach�ς�

		m_hWnd = hWnd;

		// ��������R�s�[
		if( lpLabel ) {
			m_lpLabel = new CHAR[::lstrlen(lpLabel)+1];
			::lstrcpy( m_lpLabel, lpLabel );
			::SendMessage( m_hWnd, WM_SETTEXT, 0, (LPARAM)m_lpLabel );
		}
		// �\���ƃn�C�p�[�����N�������ꍇ�̓n�C�p�[�����N�̓��x���Ɠ�����
		if( lpLabel && !lpHyperLink ) {
			m_lpHyperLink = new CHAR[::lstrlen(lpLabel)+1];
			::lstrcpy( m_lpHyperLink, lpLabel );
		}
		// �n�C�p�[�����N���ʂ̏ꍇ
		if( lpHyperLink ) {
			m_lpHyperLink = new CHAR[::lstrlen(lpHyperLink)+1];
			::lstrcpy( m_lpHyperLink, lpHyperLink );
		}

		// �|�C���g�J�[�\��(������΃f�t�H���g)
#ifndef	IDC_HAND
#define	IDC_HAND	MAKEINTRESOURCE(32649)
#endif
		m_hCursor = ::LoadCursor( NULL, IDC_HAND );

		// �A���_�[���C���t�H���g�̍쐬
		HFONT	m_hOldFont = (HFONT)::SendMessage( hWnd, WM_GETFONT, 0, 0 );
		LOGFONT	lFont;
		::GetObject( m_hOldFont, sizeof(LOGFONT), &lFont );
		lFont.lfUnderline = TRUE;
		m_hFont = ::CreateFontIndirect( &lFont );

		// ���x���̕\���̈���v�Z
		CalcLabelRectangle();

		// �X�^�C���̕ύX(�ʒm���C�l�[�u���ɂ���)
		DWORD	dwStyle = ::GetWindowLong( hWnd, GWL_STYLE );
		dwStyle |= SS_NOTIFY;
		::SetWindowLong( hWnd, GWL_STYLE, (LONG)dwStyle );

		// �R���g���[���̃T�u�N���X��
		m_lpfnOldWndProc = (WNDPROC)::SetWindowLong( hWnd, GWL_WNDPROC, (LONG)HyperLinkProc );

		// This�𖄂ߍ���
		::SetWindowLong( hWnd, GWL_USERDATA, (LONG)this );

		return	TRUE;
	}

	BOOL	Detach()
	{
		if( m_hWnd ) {
			// �T�u�N���X��������
			if( m_lpfnOldWndProc ) {
				::SetWindowLong( m_hWnd, GWL_WNDPROC, (LONG)m_lpfnOldWndProc );
				m_lpfnOldWndProc = NULL;
			}

			// �t�H���g���폜
			if( m_hFont ) {
				::DeleteObject( (HGDIOBJ)m_hFont );
				m_hFont = NULL;
			}

			// ��������폜
			if( m_lpLabel ) {
				delete[] m_lpLabel;
				m_lpLabel = NULL;
			}
			if( m_lpHyperLink ) {
				delete[] m_lpHyperLink;
				m_lpHyperLink = NULL;
			}
		}

		m_hWnd = NULL;

		return	TRUE;
	}

	BOOL	SetLabel( LPCSTR lpLabel )
	{
		if( m_lpLabel ) {
			delete[] m_lpLabel;
		}

		m_lpLabel = new CHAR[::lstrlen(lpLabel)+1];
		::lstrcpy( m_lpLabel, lpLabel );

		// �R���g���[���ɕ������ݒ�
		::SendMessage( m_hWnd, WM_SETTEXT, 0, (LPARAM)m_lpLabel );

		// ���x���̕\���̈���v�Z
		CalcLabelRectangle();
	}

	BOOL	SetHyperLink( LPCSTR lpHyperLink )
	{
		if( m_lpHyperLink ) {
			delete[] m_lpHyperLink;
		}

		m_lpHyperLink = new CHAR[::lstrlen(lpHyperLink)+1];
		::lstrcpy( m_lpHyperLink, lpHyperLink );
	}

protected:
	BOOL	CalcLabelRectangle()
	{
		if( !::IsWindow(m_hWnd) )
			return	FALSE;

		if( !m_lpLabel )
			return	FALSE;

		RECT	rcClient;
		::GetClientRect( m_hWnd, &rcClient );
		m_rcLabel = rcClient;

		HDC	hDC = ::GetDC( m_hWnd );
		HFONT	hOldFont = (HFONT)::SelectObject( hDC, m_hFont );

		// �X�^�C��
		DWORD	dwStyle = ::GetWindowLong( m_hWnd, GWL_STYLE );
		INT	nDrawStyle = DT_LEFT;
		if( dwStyle && SS_CENTER ) {
			nDrawStyle = DT_CENTER;
		} else if( dwStyle && SS_RIGHT ) {
			nDrawStyle = DT_RIGHT;
		}

		// ������\���ƕ`��̈�̌v�Z
		::DrawText( hDC, m_lpLabel, -1, &m_rcLabel, nDrawStyle | DT_WORDBREAK | DT_CALCRECT );

		::SelectObject( hDC, hOldFont );

		// �X�^�C���ɂ���ăI�t�Z�b�g���v�Z
		if( dwStyle & SS_CENTER ) {
			::OffsetRect( &m_rcLabel, (rcClient.right - m_rcLabel.right) / 2, 0 );
		} else if (dwStyle & SS_RIGHT) {
			::OffsetRect( &m_rcLabel, rcClient.right - m_rcLabel.right, 0 );
		}

		return true;
	}

	static	LRESULT CALLBACK HyperLinkProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		CHyperLink*	pHyperLink = reinterpret_cast<CHyperLink*>(::GetWindowLong( hWnd, GWL_USERDATA));

		switch( msg ) {
			case	WM_DESTROY:
				{
				// 2003/10/11 �����[�X���fix...
				WNDPROC	pWndProcOld = pHyperLink->m_lpfnOldWndProc;
				pHyperLink->Detach();
				return	CallWindowProc( pWndProcOld, hWnd, msg, wParam, lParam );
				}
				break;
			case	WM_LBUTTONDOWN: {
				POINT	pt = { LOWORD(lParam), HIWORD(lParam) };
				if( pHyperLink->m_lpLabel && pHyperLink->m_lpHyperLink ) {
					if( ::PtInRect( &pHyperLink->m_rcLabel, pt ) ) {
						::ShellExecute( hWnd, NULL, pHyperLink->m_lpHyperLink, NULL, NULL, SW_SHOWNORMAL );
						return	TRUE;
					}
				}
				}
				break;
			case	WM_MOUSEMOVE: {
				POINT	pt = { LOWORD(lParam), HIWORD(lParam) };
				if( pHyperLink->m_lpLabel && pHyperLink->m_lpHyperLink ) {
					if( pHyperLink->m_hCursor && ::PtInRect( &pHyperLink->m_rcLabel, pt ) ) {
						::SetCursor( pHyperLink->m_hCursor );
						return	TRUE;
					}
				}
				}
				break;
			case	WM_PAINT: {
				PAINTSTRUCT	ps;
				HDC	hDC = ::BeginPaint( hWnd, &ps );
				DWORD	dwStyle = ::GetWindowLong( hWnd, GWL_STYLE );
				INT	nDrawStyle = DT_LEFT;
				if( dwStyle && SS_CENTER ) {
					nDrawStyle = DT_CENTER;
				} else if( dwStyle && SS_RIGHT ) {
					nDrawStyle = DT_RIGHT;
				}

				// �A�g���r���[�g
				::SetBkMode( hDC, TRANSPARENT );
				::SetTextColor( hDC, 0x00FF0000 );

				// ������\��
				if( pHyperLink->m_lpLabel ) {
					HFONT	hOldFont = (HFONT)::SelectObject( hDC, pHyperLink->m_hFont );
					::DrawText( hDC, pHyperLink->m_lpLabel, -1, &pHyperLink->m_rcLabel, nDrawStyle | DT_WORDBREAK );
					::SelectObject( hDC, hOldFont );
				}

				::EndPaint( hWnd, &ps );
				}
				return	TRUE;
			default:
				break;
		}

		return	CallWindowProc( pHyperLink->m_lpfnOldWndProc, hWnd, msg, wParam, lParam );
	}

	HWND	m_hWnd;
	HFONT	m_hFont;
	HFONT	m_hOldFont;
	HCURSOR	m_hCursor;
	WNDPROC	m_lpfnOldWndProc;

	RECT	m_rcLabel;

	LPSTR	m_lpLabel;
	LPSTR	m_lpHyperLink;
private:
};

#endif	// !__CHYPERLINK_INCLUDED__
