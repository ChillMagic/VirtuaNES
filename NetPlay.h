//
// �l�b�g�v���C�N���X
//
#ifndef	__CNETPLAY_INCLUDED__
#define	__CNETPLAY_INCLUDED__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <winsock.h>

#include "macro.h"
#include "typedef.h"

#include <string>
using namespace std;

#define	WM_NETPLAY		(WM_APP+100)

#define	WM_NETPLAY_HOSTBYNAME	(WM_APP+101)

#define	WM_NETPLAY_ACCEPT	(WM_APP+110)
#define	WM_NETPLAY_CONNECT	(WM_APP+111)
#define	WM_NETPLAY_CLOSE	(WM_APP+112)
#define	WM_NETPLAY_ERROR	(WM_APP+113)

// for BSD style
#ifndef	INVALID_SOCKET
#define	INVALID_SOCKET	-1
#endif

// for Winsock1.x
#ifndef	SD_RECEIVE
#define	SD_RECEIVE	0
#endif
#ifndef	SD_SEND
#define	SD_SEND		1
#endif
#ifndef	SD_BOTH
#define	SD_BOTH		2
#endif

class	CNetPlay
{
public:
	CNetPlay();
	~CNetPlay();

	// ������/�J��
	BOOL	Initialize( HWND hWnd );
	void	Release();

	// �l�b�g�v���C���H
	BOOL	IsNetPlay() { return m_hWnd?TRUE:FALSE; }
	// �ڑ����H
	BOOL	IsConnect() { return m_hWnd?m_bConnect:FALSE; }
	// �ڑ����H
	BOOL	IsServer() { return m_bServer; }

	// �ʐM���C�e���V
	void	SetLatency( INT nLatency ) { m_nLatency = nLatency; }
	INT	GetLatency() { return m_nLatency; }

	// �񓯊��������b�Z�[�W�ԑ��E�C���h�E�̐ݒ�
	void	SetMsgWnd( HWND hWnd ) { m_hWndMsg = hWnd; }

	// �`���b�g���b�Z�[�W�󂯎��E�C���h�E�̐ݒ�
	void	SetChatWnd( HWND hWnd ) { m_hWndChat = hWnd; }

	// �z�X�g����IP���ǂ������`�F�b�N����(0:IP -:Error +:Host search)
	INT	ASyncHostCheck( HWND hWnd, const char* lpszHost );
	HRESULT	ASyncWndProc( HWND hWnd, WPARAM wParam, LPARAM lParam );

	// �ڑ��Ɛؒf
	BOOL	Connect( BOOL bServer, const char* lpszIP, unsigned short Port );
	void	Disconnect();

	// �f�[�^���M 0:��M�f�[�^�҂� 1�ȏ�:��M�f�[�^���� 0����:�ڑ��؂��G���[
	INT	Send( BYTE data );
	// �f�[�^��M
	// 0:��M�f�[�^�҂� 1�ȏ�:��M�f�[�^���� 0����:�ڑ��؂��G���[
	// �^�C���A�E�g����
	INT	Recv( BYTE& data );
	// �^�C���A�E�g�L��
	INT	RecvTime( BYTE& data, unsigned long timeout );

	// �����O�o�b�t�@�ւ̎�荞��
	BOOL	RecvBuffer();
	// �o�b�t�@�`�F�b�N(0:No change  +:frame add  -:no frame)
	INT	BufferCheck();
	// �����O�o�b�t�@�̃o�b�t�@�����O�o�C�g���擾
	INT	GetRecvBufferSize();

	// ��������
	INT	Sync();
	// �v���C���[��Ԃ̍X�V
	INT	ModifyPlayer( LPBYTE p1, LPBYTE p2 );

	// �`���b�g���b�Z�[�W���M
	void	ChatSend( LPCSTR lpStr );

	// Windows���b�Z�[�W�v���V�[�W��
	HRESULT	WndProc( HWND hWnd, WPARAM wParam, LPARAM lParam );

	// �ʐM�o�b�t�@
	enum {
		// �f�[�^�u���b�N�T�C�Y
		SOCKET_BLOCK_SIZE = 8,
		// �o�b�t�@�T�C�Y
		SOCKET_BUFFER_SIZE = (SOCKET_BLOCK_SIZE*32),
		// ��M���o�b�t�@�T�C�Y
		SOCKET_RECEIVE_SIZE = (SOCKET_BLOCK_SIZE*8)
	};
protected:
	// �����o�ϐ�
	HWND	m_hWnd;
	HWND	m_hWndMsg;
	HWND	m_hWndASync;
	HWND	m_hWndChat;

	HANDLE	m_hASyncTask;
	CHAR	m_HostEntry[MAXGETHOSTSTRUCT];

	BOOL	m_bServer;
	BOOL	m_bConnect;	// �ڑ����H
	INT	m_nLatency;	// ���C�e���V(�o�b�t�@�T�C�Y)
	INT	m_nFrameStep;	// �ʐM�t���[�����[�g
	INT	m_nFrameCount;	// �J�E���^

	// Ring buffer
	INT	m_nRingPtr;
	INT	m_nSendPtr;
	INT	m_nRecvPtr;
	INT	m_nRecvSize;
	BYTE	m_SendBuffer[SOCKET_BUFFER_SIZE];
	BYTE	m_RecvBuffer[SOCKET_BUFFER_SIZE];

	// WINSOCK
	WSADATA	m_WSAdata;
	SOCKET	m_SocketConnect;
	SOCKET	m_SocketData;
	SOCKET	m_SocketChat;

	struct sockaddr_in	m_SAddr_Server;
	struct sockaddr_in	m_SAddr_Client;
private:
};

extern	CNetPlay	NetPlay;

#endif	// !__CNETPLAY_INCLUDED__
