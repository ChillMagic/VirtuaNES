//
// �`���b�g�_�C�A���O�N���X
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mbstring.h>
#include <shlwapi.h>

#include <string>
using namespace std;

#include "typedef.h"
#include "macro.h"

#include "VirtuaNESres.h"
#include "DebugOut.h"
#include "App.h"
#include "Pathlib.h"

#include "EmuThread.h"
#include "VsUnisystem.h"

#include "Wnd.h"
#include "DipSwitchDlg.h"

// ���b�Z�[�W
DLG_MESSAGE_BEGIN(CDipSwitchDlg)
DLG_ON_MESSAGE( WM_INITDIALOG,	OnInitDialog )

// �R�}���h
DLG_COMMAND_BEGIN()
DLG_ON_COMMAND( IDOK, OnOK )
DLG_ON_COMMAND( IDCANCEL, OnCancel )
DLG_COMMAND_END()
// Notify ���b�Z�[�W
DLG_NOTIFY_BEGIN()
DLG_NOTIFY_END()
DLG_MESSAGE_END()

INT	CDipSwitchDlg::DoModal( HWND hWndParent )
{
	return	::DialogBoxParam( CApp::GetPlugin(), MAKEINTRESOURCE(IDD_EXT_VSUNISYSTEM),
				hWndParent, g_DlgProc, (LPARAM)this );
}


DLGMSG	CDipSwitchDlg::OnInitDialog( DLGMSGPARAM )
{
//	DEBUGOUT( "CDipSwitchDlg::OnInitDialog\n" );

	for( INT i = IDC_EVS_DIPCOMBO0; i <= IDC_EVS_DIPCOMBO7; i++ ) {
		::SendDlgItemMessage( m_hWnd, i, CB_RESETCONTENT, 0, 0 );
	}

	BYTE		val = Emu.GetNES()->GetVSDipSwitch();
	VSDIPSWITCH*	dip = Emu.GetNES()->GetVSDipSwitchTable();

DEBUGOUT( "GET DIPSWITCH:%02X\n", val );

	BYTE	mask;

	INT	nStatic = IDC_EVS_DIPNAME0;
	INT	nCombo  = IDC_EVS_DIPCOMBO0;
	BOOL	bFlag;
	INT	nCount, nSelect;

	bFlag = FALSE;
	nCount = nSelect = 0;
	for(;;) {
		if( dip->name == NULL && dip->value == 0x0000 ) {
			break;
		} else if( dip->value == 0x00FF ) {
			bFlag = FALSE;
			::SendDlgItemMessage( m_hWnd, nCombo, CB_SETCURSEL, (WPARAM)nSelect, 0 );
			nCombo++;
		} else if( !bFlag ) {
			bFlag = TRUE;
			::SetDlgItemText( m_hWnd, nStatic, (LPCTSTR)dip->name );
			mask = dip->value>>8;
			nCount = 0;
			nStatic++;
		} else {
			if( dip->value == (val & mask) )
				nSelect = nCount;
			::SendDlgItemMessage( m_hWnd, nCombo, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)dip->name );
			::SendDlgItemMessage( m_hWnd, nCombo, CB_SETITEMDATA, (WPARAM)nCount, (LPARAM)(dip->value&0xFF) );
			nCount++;
		}
		dip++;
	}
	m_nDispCount = nStatic-IDC_EVS_DIPNAME0;

	// �g��Ȃ��z�͔�\���ɂ���
	for( ; nStatic <= IDC_EVS_DIPNAME7; nStatic++, nCombo++ ) {
		::ShowWindow( ::GetDlgItem( m_hWnd, nStatic ), SW_HIDE );
		::ShowWindow( ::GetDlgItem( m_hWnd, nCombo ), SW_HIDE );
	}

	return	TRUE;
}

DLGCMD	CDipSwitchDlg::OnOK( DLGCMDPARAM )
{
//	DEBUGOUT( "CDipSwitchDlg::OnOK\n" );

	// �I������Ă���z��ItemData���擾����DipSwitch�f�[�^����蒼��(OnInitDialog��ItemData��ݒ�ς�)
	BYTE	dipval = 0;
	for( INT i = IDC_EVS_DIPCOMBO0; i < IDC_EVS_DIPCOMBO0+m_nDispCount; i++ ) {
		INT	sel = ::SendDlgItemMessage( m_hWnd, i, CB_GETCURSEL, 0, 0 );
		DWORD	val = (DWORD)::SendDlgItemMessage( m_hWnd, i, CB_GETITEMDATA, (WPARAM)sel, 0 );

		dipval |= val & 0xFF;
	}

	Emu.GetNES()->SetVSDipSwitch( dipval );

DEBUGOUT( "SET DIPSWITCH:%02X\n", dipval );

	::EndDialog( m_hWnd, IDOK );
}

DLGCMD	CDipSwitchDlg::OnCancel( DLGCMDPARAM )
{
//	DEBUGOUT( "CDipSwitchDlg::OnCancel\n" );
	::EndDialog( m_hWnd, IDCANCEL );
}

