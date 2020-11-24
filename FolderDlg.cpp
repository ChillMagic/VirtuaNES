//
// �t�H���_�_�C�A���O�N���X
//
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
using namespace std;

#include "VirtuaNESres.h"
#include "DebugOut.h"
#include "App.h"
#include "Pathlib.h"

#include "Wnd.h"
#include "FolderDlg.h"

DLG_MESSAGE_BEGIN(CFolderDlg)
// ���b�Z�[�W
DLG_ON_MESSAGE( WM_INITDIALOG,	OnInitDialog )
// �R�}���h
DLG_COMMAND_BEGIN()
DLG_ON_COMMAND( IDOK, OnOK )
DLG_ON_COMMAND( IDCANCEL, OnCancel )
DLG_ON_COMMAND( IDDEFAULT, OnDefault )
DLG_ON_COMMAND( IDC_FLD_ROM_BROWSE, OnRomBrowse )
DLG_ON_COMMAND( IDC_FLD_SAVE_BROWSE, OnSaveBrowse )
DLG_ON_COMMAND( IDC_FLD_STATE_BROWSE, OnStateBrowse )
DLG_ON_COMMAND( IDC_FLD_SNAPSHOT_BROWSE, OnSnapshotBrowse )
DLG_ON_COMMAND( IDC_FLD_MOVIE_BROWSE, OnMovieBrowse )
DLG_ON_COMMAND( IDC_FLD_WAVE_BROWSE, OnWaveBrowse )
DLG_ON_COMMAND( IDC_FLD_CHEAT_BROWSE, OnCheatBrowse )
DLG_ON_COMMAND( IDC_FLD_IPS_BROWSE, OnIpsBrowse )
DLG_COMMAND_END()
DLG_MESSAGE_END()

CFolderDlg::CFolderDlg()
{
}

CFolderDlg::~CFolderDlg()
{
}

INT	CFolderDlg::DoModal( HWND hWndParent )
{
	return	::DialogBoxParam( CApp::GetPlugin(), MAKEINTRESOURCE(IDD_CFG_FOLDER),
				hWndParent, g_DlgProc, (LPARAM)this );
}

void	CFolderDlg::OnInitialMember()
{
	BTNCHECK( IDC_FLD_ROM_USE,	Config.path.bRomPath );
	BTNCHECK( IDC_FLD_SAVE_USE,	Config.path.bSavePath );
	BTNCHECK( IDC_FLD_STATE_USE,	Config.path.bStatePath );
	BTNCHECK( IDC_FLD_SNAPSHOT_USE,	Config.path.bSnapshotPath );
	BTNCHECK( IDC_FLD_MOVIE_USE,	Config.path.bMoviePath );
	BTNCHECK( IDC_FLD_WAVE_USE,	Config.path.bWavePath );
	BTNCHECK( IDC_FLD_CHEAT_USE,	Config.path.bCheatPath );
	BTNCHECK( IDC_FLD_IPS_USE,	Config.path.bIpsPath );

	::SetDlgItemText( m_hWnd, IDC_FLD_ROM_EDIT, Config.path.szRomPath );
	::SetDlgItemText( m_hWnd, IDC_FLD_SAVE_EDIT, Config.path.szSavePath );
	::SetDlgItemText( m_hWnd, IDC_FLD_STATE_EDIT, Config.path.szStatePath );
	::SetDlgItemText( m_hWnd, IDC_FLD_SNAPSHOT_EDIT, Config.path.szSnapshotPath );
	::SetDlgItemText( m_hWnd, IDC_FLD_MOVIE_EDIT, Config.path.szMoviePath );
	::SetDlgItemText( m_hWnd, IDC_FLD_WAVE_EDIT, Config.path.szWavePath );
	::SetDlgItemText( m_hWnd, IDC_FLD_CHEAT_EDIT, Config.path.szCheatPath );
	::SetDlgItemText( m_hWnd, IDC_FLD_IPS_EDIT, Config.path.szIpsPath );
}

void	CFolderDlg::PathCheck( LPSTR lpszPath )
{
	INT	len = ::strlen( lpszPath );

	if( len > 3 ) {
		if( isleadbyte( (UINT)lpszPath[len-2] ) ) {
			// MBCS�Ł��������ꍇ
				::strcat( lpszPath, "\\" );
		} else {
			if( lpszPath[ len-1 ] != '\\' ) {
				::strcat( lpszPath, "\\" );
			}
		}
	}
}

DLGMSG	CFolderDlg::OnInitDialog( DLGMSGPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnInitDialog\n" );
	m_ConfigSave = Config.path;
	OnInitialMember();

	return	TRUE;
}

DLGCMD	CFolderDlg::OnOK( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnOK\n" );
	Config.path.bRomPath      = IsBTNCHECK( IDC_FLD_ROM_USE );
	Config.path.bSavePath     = IsBTNCHECK( IDC_FLD_SAVE_USE );
	Config.path.bStatePath    = IsBTNCHECK( IDC_FLD_STATE_USE );
	Config.path.bSnapshotPath = IsBTNCHECK( IDC_FLD_SNAPSHOT_USE );
	Config.path.bMoviePath    = IsBTNCHECK( IDC_FLD_MOVIE_USE );
	Config.path.bWavePath     = IsBTNCHECK( IDC_FLD_WAVE_USE );
	Config.path.bCheatPath    = IsBTNCHECK( IDC_FLD_CHEAT_USE );
	Config.path.bIpsPath      = IsBTNCHECK( IDC_FLD_IPS_USE );

	::GetDlgItemText( m_hWnd, IDC_FLD_ROM_EDIT, Config.path.szRomPath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_SAVE_EDIT, Config.path.szSavePath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_STATE_EDIT, Config.path.szStatePath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_SNAPSHOT_EDIT, Config.path.szSnapshotPath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_MOVIE_EDIT, Config.path.szMoviePath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_WAVE_EDIT, Config.path.szWavePath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_CHEAT_EDIT, Config.path.szCheatPath, _MAX_PATH );
	::GetDlgItemText( m_hWnd, IDC_FLD_IPS_EDIT, Config.path.szIpsPath, _MAX_PATH );

	PathCheck( Config.path.szRomPath );
	PathCheck( Config.path.szSavePath );
	PathCheck( Config.path.szStatePath );
	PathCheck( Config.path.szSnapshotPath );
	PathCheck( Config.path.szMoviePath );
	PathCheck( Config.path.szWavePath );
	PathCheck( Config.path.szCheatPath );
	PathCheck( Config.path.szIpsPath );

	::EndDialog( m_hWnd, IDOK );
}

DLGCMD	CFolderDlg::OnCancel( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnCancel\n" );
	Config.path = m_ConfigSave;
	::EndDialog( m_hWnd, IDCANCEL );
}

DLGCMD	CFolderDlg::OnDefault( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnDefault\n" );
	Config.path.Default();
	OnInitialMember();
}

DLGCMD	CFolderDlg::OnRomBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnRomBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_ROM_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_ROM_EDIT, szFolder );
		BTNCHECK( IDC_FLD_ROM_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnSaveBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnSaveBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_SAVE_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_SAVE_EDIT, szFolder );
		BTNCHECK( IDC_FLD_SAVE_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnStateBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnStateBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_STATE_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_STATE_EDIT, szFolder );
		BTNCHECK( IDC_FLD_STATE_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnSnapshotBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnSnapshotBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_SNAPSHOT_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_SNAPSHOT_EDIT, szFolder );
		BTNCHECK( IDC_FLD_SNAPSHOT_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnMovieBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnMovieBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_MOVIE_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_MOVIE_EDIT, szFolder );
		BTNCHECK( IDC_FLD_MOVIE_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnWaveBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnWaveBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_WAVE_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_WAVE_EDIT, szFolder );
		BTNCHECK( IDC_FLD_WAVE_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnCheatBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnCheatBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_CHEAT_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_CHEAT_EDIT, szFolder );
		BTNCHECK( IDC_FLD_CHEAT_USE, TRUE );
	}
}

DLGCMD	CFolderDlg::OnIpsBrowse( DLGCMDPARAM )
{
//	DEBUGOUT( "CFolderDlg::OnIpsBrowse\n" );
	CHAR	szTemp[_MAX_PATH];
	::GetDlgItemText( m_hWnd, IDC_FLD_IPS_EDIT, szTemp, _MAX_PATH );

	CHAR	szFolder[_MAX_PATH];
	string	pathstr = CPathlib::CreatePath( CApp::GetModulePath(), szTemp );
	::lstrcpy( szFolder, pathstr.c_str() );
DEBUGOUT( "Path:%s\n", szFolder );

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_BROWSE, szTitle, sizeof(szTitle) );

	if( CPathlib::SelectFolder( m_hWnd, szTitle, szFolder ) ) {
		::SetDlgItemText( m_hWnd, IDC_FLD_IPS_EDIT, szFolder );
		BTNCHECK( IDC_FLD_IPS_USE, TRUE );
	}
}

