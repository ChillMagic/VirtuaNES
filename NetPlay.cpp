//
// �l�b�g�v���C�N���X
//
// �����I��WinSock Lib�������N
#pragma comment(lib, "wsock32.lib")

#include "DebugOut.h"
#include "NetPlay.h"

#define	CLOSESOCKET(soc) if((soc)!=INVALID_SOCKET){::closesocket((soc));(soc)=INVALID_SOCKET;}

static	char*	SocketErrorDump( int eno );

CNetPlay	NetPlay;

CNetPlay::CNetPlay()
{
	m_hWnd = m_hWndMsg = m_hWndChat = NULL;
	m_bConnect = FALSE;

	m_SocketConnect = INVALID_SOCKET;
	m_SocketData = INVALID_SOCKET;
	m_SocketChat = INVALID_SOCKET;

	m_nLatency = 0;
	m_nFrameCount = 0;
	m_nFrameStep = 0;

	m_hASyncTask = NULL;
}

CNetPlay::~CNetPlay()
{
	// �Ƃ肠����
	Release();
}

BOOL	CNetPlay::Initialize( HWND hWnd )
{
	// �Ƃ肠����
	Release();

	// WinSock DLL�̏�����
	if( ::WSAStartup( MAKEWORD(1,1), &m_WSAdata ) )
		return	FALSE;

	// �o�[�W�����Ⴄ����`��
	if( m_WSAdata.wVersion != MAKEWORD(1,1) ) {
		::WSACleanup();
		return	FALSE;
	}

	m_hWnd = hWnd;
	return	TRUE;
}

void	CNetPlay::Release()
{
	Disconnect();

	if( m_hWnd ) {
		::WSACleanup();
		m_hWnd = NULL;
	}
}

INT	CNetPlay::ASyncHostCheck( HWND hWnd, const char* lpszHost )
{
DEBUGOUT( "CNetPlay:ASyncHostCheck [%s]\n", lpszHost );

	unsigned long IP_address = ::inet_addr( lpszHost );
	if( IP_address != INADDR_NONE ) {
		DEBUGOUT( "CNetPlay:��IP����\n" );
		return	0;
	}

	m_hWndASync = hWnd;

	// �z�X�g�����J�n
	m_hASyncTask = ::WSAAsyncGetHostByName( hWnd, WM_NETPLAY_HOSTBYNAME, lpszHost, m_HostEntry, MAXGETHOSTSTRUCT );

	if( m_hASyncTask ) {
		return	1;
	}

	return	-1;
}

HRESULT	CNetPlay::ASyncWndProc( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
DEBUGOUT( "CNetPlay:ASyncWndProc\n" );

	if( WSAGETASYNCERROR(lParam) ) {
DEBUGOUT( "CNetPlay:ASyncWndProc error.[%s]\n", SocketErrorDump( WSAGETASYNCERROR(lParam) ) );
		m_hWndASync = NULL;
		return	0;
	}

	if( m_hASyncTask == (HANDLE)wParam ) {
		if( m_hWndASync ) {
			m_hWndASync = NULL;

			return	*((unsigned long *)((((struct hostent FAR *)m_HostEntry)->h_addr_list)[0]));
		}
	}

	return	0L;
}

BOOL	CNetPlay::Connect( BOOL bServer, const char* lpszIP, unsigned short Port )
{
	if( !m_hWnd )
		return	FALSE;

	m_bServer = bServer;

	if( bServer ) {
	// Server
		// �ڑ��ʒm�\�P�b�g�쐬
		if( m_SocketConnect == INVALID_SOCKET ) {
			m_SocketConnect = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
			if( m_SocketConnect == INVALID_SOCKET ) {
				DEBUGOUT( "CNetPlay:socket failed.\n" );
				return	FALSE;
			}
		}

		// �ė��p�������Ă݂�
		unsigned long ulOpt = 1;
		if( ::setsockopt( m_SocketConnect, SOL_SOCKET, SO_REUSEADDR, (const char*)&ulOpt, sizeof(ulOpt) ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:setsockopt failed. (SO_REUSEADDR)\n" );
			CLOSESOCKET( m_SocketConnect );
			return	FALSE;
		}

		// �|�[�g�ƌ��т���
		ZEROMEMORY( &m_SAddr_Server, sizeof(m_SAddr_Server) );
		m_SAddr_Server.sin_family      = AF_INET;
		m_SAddr_Server.sin_addr.s_addr = ::htonl( INADDR_ANY );
		m_SAddr_Server.sin_port        = ::htons( Port );
		if( ::bind( m_SocketConnect, (struct sockaddr *)&m_SAddr_Server, sizeof(m_SAddr_Server) ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:bind failed.\n" );
			CLOSESOCKET( m_SocketConnect );
			return	FALSE;
		}
//-----------------
		// �`���b�g�p�\�P�b�g�쐬
		m_SocketChat = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
		if( m_SocketChat == INVALID_SOCKET ) {
			DEBUGOUT( "create socket failed.[chat]\n" );
			Disconnect();
			return	FALSE;
		}
		// �|�[�g�ɐڑ�
		if( ::bind( m_SocketChat, (struct sockaddr *)&m_SAddr_Server, sizeof(m_SAddr_Server) ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:connect failed. [chat]\n" );
			Disconnect();
			return	FALSE;
		}
		// �u���b�L���O���[�h�ݒ�
		unsigned long ulArg = 1;
		if( ::ioctlsocket( m_SocketChat, FIONBIO, &ulArg ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:ioctlsocket failed.[chat]\n" );
			Disconnect();
			return	FALSE;
		}
//-----------------
		// �ڑ��v���C�x���g�̐ݒ�
		if( ::WSAAsyncSelect( m_SocketConnect, m_hWnd, WM_NETPLAY, FD_ACCEPT ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.\n" );
			CLOSESOCKET( m_SocketConnect );
			return	FALSE;
		}

		// �ڑ��v����t�J�n���Ă݂�
		if( ::listen( m_SocketConnect, 1 ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:listen failed.\n" );
			CLOSESOCKET( m_SocketConnect );
			return	FALSE;
		}
	} else {
	// Client
		unsigned long	ulOpt;
		// IP�A�h���X�H
		unsigned long IP_address = ::inet_addr( lpszIP );
		if( IP_address == INADDR_NONE ) {
			DEBUGOUT( "CNetPlay:IP�A�h���X���s���ł��B\"%s\"\n", lpszIP );
			return	FALSE;
		}

		// �f�[�^�ʐM�\�P�b�g�쐬
		m_SocketData = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( m_SocketData == INVALID_SOCKET ) {
			DEBUGOUT( "CNetPlay:socket failed.\n" );
			return	FALSE;
		}

		// �ė��p�������Ă݂�
		ulOpt = 1;
		if( ::setsockopt( m_SocketData, SOL_SOCKET, SO_REUSEADDR, (const char*)&ulOpt, sizeof(ulOpt) ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:setsockopt failed. (SO_REUSEADDR)\n" );
			CLOSESOCKET( m_SocketData );
			return	FALSE;
		}

		// Nagle�A���S���Y���̖�����
		ulOpt = 1;
		if( ::setsockopt( m_SocketData, IPPROTO_TCP, TCP_NODELAY, (const char*)&ulOpt, sizeof(ulOpt) ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:setsockopt failed.\n" );
			CLOSESOCKET( m_SocketData );
			return	FALSE;
		}

		// �u���b�L���O���[�h�ݒ�
		unsigned long	ulArg = 1;
		if( ::ioctlsocket( m_SocketData, FIONBIO, &ulArg ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:ioctlsocket failed.\n" );
			CLOSESOCKET( m_SocketData );
			return	FALSE;
		}

//-----------------
		// �`���b�g�p�\�P�b�g�쐬
		m_SocketChat = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
		if( m_SocketChat == INVALID_SOCKET ) {
			DEBUGOUT( "create socket failed.[chat]\n" );
			Disconnect();
			return	FALSE;
		}
		// �u���b�L���O���[�h�ݒ�
//		unsigned long ulArg = 1;
		ulArg = 1;
		if( ::ioctlsocket( m_SocketChat, FIONBIO, &ulArg ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:ioctlsocket failed.[chat]\n" );
			Disconnect();
			return	FALSE;
		}
//-----------------

		// �ڑ������C�x���g�̐ݒ�
		if( ::WSAAsyncSelect( m_SocketData, m_hWnd, WM_NETPLAY, FD_CONNECT ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.\n" );
			CLOSESOCKET( m_SocketData );
			return	FALSE;
		}

		// �ڑ���v�����Ă݂�
		ZEROMEMORY( &m_SAddr_Server, sizeof(m_SAddr_Server) );
		m_SAddr_Server.sin_family      = AF_INET;
		m_SAddr_Server.sin_addr.s_addr = IP_address;
		m_SAddr_Server.sin_port        = ::htons( Port );
		if( ::connect( m_SocketData, (struct sockaddr *)&m_SAddr_Server, sizeof(m_SAddr_Server) ) == SOCKET_ERROR ) {
			if( ::WSAGetLastError() != WSAEWOULDBLOCK ) {
				DEBUGOUT( "CNetPlay:connect failed.\n" );
				CLOSESOCKET( m_SocketData );
				return	FALSE;
			}
		}
	}

	return	TRUE;
}

void	CNetPlay::Disconnect()
{
#if	defined(_DEBUG)||defined(_DEBUGOUT)
if( m_bConnect ) {
DEBUGOUT( "CNetPlay::Disconnect\n" );
}
#endif
	if( m_hASyncTask ) {
		::WSACancelAsyncRequest( m_hASyncTask );
		m_hASyncTask = NULL;
	}

	// �\�P�b�g���V���b�g�_�E�����Ĕj��
	if( m_SocketConnect != INVALID_SOCKET ) {
		::shutdown( m_SocketConnect, SD_BOTH );
		CLOSESOCKET( m_SocketConnect );
	}
	if( m_SocketData != INVALID_SOCKET ) {
		::shutdown( m_SocketData, SD_BOTH );
		CLOSESOCKET( m_SocketData );
	}
	if( m_SocketChat != INVALID_SOCKET ) {
		::shutdown( m_SocketChat, SD_BOTH );
		CLOSESOCKET( m_SocketChat );
	}

	m_bConnect = FALSE;
}

INT	CNetPlay::Send( BYTE data )
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	-1L;

	while( TRUE ) {
		if( ::send( m_SocketData, (char*)&data, sizeof(BYTE), 0 ) == SOCKET_ERROR ) {
			// �u���b�N���ꂽ�����m��Ȃ��̂ōēx����
			if( ::WSAGetLastError() == WSAEWOULDBLOCK ) {
				::Sleep(0);	// �ł܂�Ȃ��[�u
				continue;
			} else {
			// �v���I�G���[���ۂ�
				DEBUGOUT( "CNetPlay:send failed. code=%d\n", ::WSAGetLastError() );
				Disconnect();
				return	-1L;
			}
		} else {
			break;
		}
	}
	return	0L;
}

INT	CNetPlay::Recv( BYTE& data )
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	-1L;

	// �f�[�^���͂��Ă��邩���m�F
	unsigned long	len = 0;
	if( ::ioctlsocket( m_SocketData, FIONREAD, (unsigned long*)&len ) == SOCKET_ERROR ) {
		DEBUGOUT( "CNetPlay:ioctlsocket failed.\n" );
		Disconnect();
		return	-1L;
	}

	if( !len ) {
		// �f�[�^���͂��Ă��Ȃ�
		return	0L;
	} else {
		// 1�o�C�g�ǂݍ���
		if( ::recv( m_SocketData, (char*)&data, sizeof(BYTE), 0 ) == SOCKET_ERROR ) {
			DEBUGOUT( "CNetPlay:recv failed.\n" );
			Disconnect();
			return	-1L;
		}
	}

	return	len;
}

INT	CNetPlay::RecvTime( BYTE& data, unsigned long timeout )
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	-1L;

	INT	ret;
	DWORD	dwTimeOut = ::timeGetTime();
	while( (ret = NetPlay.Recv( data )) == 0 ) {
		// �ł܂�Ȃ��[�u
		::Sleep( 0 );
		// �^�C���A�E�g�̃`�F�b�N
		if( (::timeGetTime()-dwTimeOut) > timeout ) {
			return	-1;
		}
	}
	return	ret;
}

BOOL	CNetPlay::RecvBuffer()
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	FALSE;

	BYTE	buf[SOCKET_RECEIVE_SIZE];
	INT	recvsize = ::recv( m_SocketData, (char*)buf, SOCKET_RECEIVE_SIZE, 0 );
	if( recvsize == 0 ) {
		return	FALSE;
	} else if( recvsize == SOCKET_ERROR ) {
		if( ::WSAGetLastError() == WSAEWOULDBLOCK ) {
			return	TRUE;
		} else {
DEBUGOUT( "CNetPlay::RecvBuffer failed. [%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
			return	FALSE;
		}
	} else {
		INT	p = m_nRecvPtr;
		for( INT i = 0; i < recvsize; i++ ) {
			m_RecvBuffer[p] = buf[i];
			p = (p+1) & SOCKET_BUFFER_SIZE-1;
		}
		m_nRecvPtr = p;
		m_nRecvSize += recvsize;
	}
	return	TRUE;
}

INT	CNetPlay::GetRecvBufferSize()
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	0;

	return	m_nRecvSize;
}

BOOL	CNetPlay::BufferCheck()
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	0;

	// LAN
	if( m_nLatency == 0 && m_nRecvSize < SOCKET_BLOCK_SIZE ) {
		return	-1;
	}

	// Frame control
	// ���������H
	if( m_nRecvSize < SOCKET_BLOCK_SIZE ) {
		return	-1;	// �����҂��Ă���
	}
	// �x�������H
	if( m_nRecvSize > ((m_nLatency+2)*SOCKET_BLOCK_SIZE) ) {
		return	1;	// �����i�߂Ă���
	}
	return	0;
}

// �����O����(���C�e���V�̕�������ɑ��M���ē��������)
INT	CNetPlay::Sync()
{
BYTE	senddata[SOCKET_BLOCK_SIZE];

DEBUGOUT( "CNetPlay::Sync\n" );

	ZEROMEMORY( senddata, sizeof(senddata) );

	m_nFrameCount = 0;
	m_nRingPtr = m_nSendPtr = m_nRecvPtr = 0;
	m_nRecvSize = 0;

DEBUGOUT( "CNetPlay::Sync sending...\n" );

	// �f�[�^���M
	for( INT i = 0; i < m_nLatency+1; i++ ) {
		while( TRUE ) {
			if( ::send( m_SocketData, (char*)senddata, SOCKET_BLOCK_SIZE, 0 ) == SOCKET_ERROR ) {
				// �u���b�N���ꂽ�����m��Ȃ��̂ōēx����
				if( ::WSAGetLastError() == WSAEWOULDBLOCK ) {
DEBUGOUT( "send::WSAEWOULDBLOCK!!\n" );
					::Sleep(0);	// �ł܂�Ȃ��[�u
					continue;
				} else {
				// �v���I�G���[���ۂ�
DEBUGOUT( "CNetPlay:Sync send failed. [%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
					Disconnect();
					return	-1L;
				}
			} else {
				break;
			}
		}
		m_nSendPtr = (m_nSendPtr+SOCKET_BLOCK_SIZE) & SOCKET_BUFFER_SIZE-1;
	}

	// ����f�[�^�̃o�b�t�@�����O�f�[�^�҂�(10�b�Ń^�C���A�E�g)
	DWORD	dwTime = ::timeGetTime();
	while( m_nRecvSize < (m_nLatency+1)*SOCKET_BLOCK_SIZE ) {
		if( !RecvBuffer() ) {
			DEBUGOUT( "CNetPlay:recv error.\n" );
			Disconnect();
			return	-1;
		}

		if( (::timeGetTime()-dwTime) > 10*1000 ) {
			DEBUGOUT( "CNetPlay:Sync recv timeout.\n" );
			Disconnect();
			return	-1;
		}
		::Sleep( 1 );
	}

DEBUGOUT( "CNetPlay::Sync OK!\n" );

	return	0;
}

// �v���C���[�L�[�̍X�V
INT	CNetPlay::ModifyPlayer( LPBYTE p1, LPBYTE p2 )
{
	if( !m_hWnd || !m_bConnect || m_SocketData == INVALID_SOCKET )
		return	-1L;

	// ����ׂ��|�C���g�ő��M
	if( m_nFrameCount == 0 ) {
		while( TRUE ) {
			if( ::send( m_SocketData, (char*)p1, SOCKET_BLOCK_SIZE, 0 ) == SOCKET_ERROR ) {
				// �u���b�N���ꂽ�����m��Ȃ��̂ōēx����
				if( ::WSAGetLastError() == WSAEWOULDBLOCK ) {
DEBUGOUT( "send::WSAEWOULDBLOCK!!\n" );
					::Sleep(0);	// �ł܂�Ȃ��[�u
					continue;
				} else {
				// �v���I�G���[���ۂ�
					DEBUGOUT( "CNetPlay:ModifyPlayer send failed. code=%d\n", ::WSAGetLastError() );
					Disconnect();
					return	-1L;
				}
			} else {
				break;
			}
		}

		// �o�b�t�@�ɕ��荞��
		for( INT i = 0; i < SOCKET_BLOCK_SIZE; i++ ) {
			m_SendBuffer[ m_nSendPtr ] = p1[i];
			m_nSendPtr = (m_nSendPtr+1) & SOCKET_BUFFER_SIZE-1;
		}
	}

	// ����f�[�^�҂�(10�b�Ń^�C���A�E�g)
	DWORD	dwTime = ::timeGetTime();
	while( m_nRecvSize < SOCKET_BLOCK_SIZE ) {
		if( !RecvBuffer() ) {
			DEBUGOUT( "CNetPlay:ModifyPlayer recv error.\n" );
			Disconnect();
			return	-1;
		}
		if( (::timeGetTime()-dwTime) > 10*1000 ) {
			DEBUGOUT( "CNetPlay:ModifyPlayer recv timeout.\n" );
			Disconnect();
			return	-1;
		}
		::Sleep( 1 );
	}

	// ���X�V
	INT	p = m_nRingPtr;
	for( INT i = 0; i < SOCKET_BLOCK_SIZE; i++ ) {
		p1[i] = m_SendBuffer[ p ];
		p2[i] = m_RecvBuffer[ p ];
		p = (p+1) & SOCKET_BUFFER_SIZE-1;
	}

	INT	Count = m_nFrameCount;

	// �X�e�b�v�X�V
	if( ++m_nFrameCount > m_nFrameStep ) {
		m_nFrameCount = 0;

		m_nRingPtr = (m_nRingPtr+SOCKET_BLOCK_SIZE) & SOCKET_BUFFER_SIZE-1;
		m_nRecvSize -= SOCKET_BLOCK_SIZE;
	}

	return	Count;
}

void	CNetPlay::ChatSend( LPCSTR lpStr )
{
	if( !m_hWnd || !m_bConnect || m_SocketChat == INVALID_SOCKET )
		return;

	if( m_bServer ) {
DEBUGOUT( "ChatSend Server:%s", lpStr );
		if( ::sendto( m_SocketChat, (char*)lpStr, ::strlen(lpStr)+1, 0, (struct sockaddr *)&m_SAddr_Client, sizeof(m_SAddr_Client) ) == SOCKET_ERROR ) {
			DEBUGOUT( "ChatSend failed. Server:[%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
		}
	} else {
DEBUGOUT( "ChatSend Client:%s", lpStr );
		if( ::sendto( m_SocketChat, (char*)lpStr, ::strlen(lpStr)+1, 0, (struct sockaddr *)&m_SAddr_Server, sizeof(m_SAddr_Server) ) == SOCKET_ERROR ) {
			DEBUGOUT( "ChatSend failed. Server:[%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
		}
	}
}

HRESULT	CNetPlay::WndProc( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
	// �G���[�H
	if( WSAGETSELECTERROR(lParam) ) {
		DEBUGOUT( "CNetPlay::WndProc error.[%s]\n", SocketErrorDump( WSAGETSELECTERROR(lParam) ) );

		Disconnect();
		if( m_hWndMsg ) {
			::PostMessage( m_hWndMsg, WM_NETPLAY_CLOSE, 0, 0 );
		}

		return	0L;
	}

	switch( WSAGETSELECTEVENT(lParam) ) {
		case	FD_ACCEPT: {
			DEBUGOUT( "Accepting...." );
			ZEROMEMORY( &m_SAddr_Client, sizeof(m_SAddr_Client) );
			int	len = sizeof(m_SAddr_Client);
			m_SocketData = ::accept( m_SocketConnect, (sockaddr*)&m_SAddr_Client, &len );

			// �ڑ��p�\�P�b�g�͕���
			::shutdown( m_SocketConnect, SD_BOTH );
			CLOSESOCKET( m_SocketConnect );

			if( m_SocketData == INVALID_SOCKET ) {
				DEBUGOUT( "failed.\n" );
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			DEBUGOUT( "done.\n" );

			// Nagle�A���S���Y���̖�����
			unsigned long ulOpt = 1;
			if( ::setsockopt( m_SocketData, IPPROTO_TCP, TCP_NODELAY, (const char*)&ulOpt, sizeof(ulOpt) ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:setsockopt failed.\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			// �u���b�L���O���[�h�ݒ�
			unsigned long ulArg = 1;
			if( ::ioctlsocket( m_SocketData, FIONBIO, &ulArg ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:ioctlsocket failed.\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			// �񓯊��C�x���g�̐ݒ�
			if( ::WSAAsyncSelect( m_SocketChat, m_hWnd, WM_NETPLAY, FD_READ ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.[CONNECT chat]\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			// �񓯊��C�x���g�̐ݒ�
			if( ::WSAAsyncSelect( m_SocketData, m_hWnd, WM_NETPLAY, FD_CLOSE ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.[ACCEPT data]\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			m_bConnect = TRUE;
			if( m_hWndMsg ) {
				::PostMessage( m_hWndMsg, WM_NETPLAY_ACCEPT, 0, 0 );
			}
			break;
			}

		case	FD_CONNECT: {
			DEBUGOUT( "Connection done.\n" );

			// 1�o�C�g�����_�~�[�f�[�^�𑗂�(�����Ԉ���Ă�C������c)
			if( ::sendto( m_SocketChat, (char*)"", 1, 0, (struct sockaddr *)&m_SAddr_Server, sizeof(m_SAddr_Server) ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:send failed. Client:[%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			// �񓯊��C�x���g�̐ݒ�
			if( ::WSAAsyncSelect( m_SocketChat, m_hWnd, WM_NETPLAY, FD_READ ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.[CONNECT chat]\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}

			// �񓯊��C�x���g�̐ݒ�
			if( ::WSAAsyncSelect( m_SocketData, m_hWnd, WM_NETPLAY, FD_CLOSE ) == SOCKET_ERROR ) {
				DEBUGOUT( "CNetPlay:WSAAsyncSelect failed.[CONNECT data]\n" );
				Disconnect();
				if( m_hWndMsg ) {
					::PostMessage( m_hWndMsg, WM_NETPLAY_ERROR, 0, 0 );
				}
				return	0L;
			}
			m_bConnect = TRUE;
			if( m_hWndMsg ) {
				::PostMessage( m_hWndMsg, WM_NETPLAY_CONNECT, 0, 0 );
			}
			break;
			}

		case	FD_CLOSE: {
			DEBUGOUT( "Connection close.\n" );
			if( m_bConnect && m_hWndMsg ) {
				::PostMessage( m_hWndMsg, WM_NETPLAY_CLOSE, 0, 0 );
			}
			Disconnect();
			break;
			}

		case	FD_READ: {
// error is ignored :p
//			DEBUGOUT( "FD_READ\n" );
			INT	recvsize = 0;
			INT	size = sizeof(struct sockaddr_in);
			CHAR	szBuf[256+1];

			if( m_bServer ) {
				recvsize = ::recvfrom( m_SocketChat, (char*)szBuf, sizeof(szBuf)-1, 0, (struct sockaddr *)&m_SAddr_Client, &size );
			} else {
				recvsize = ::recvfrom( m_SocketChat, (char*)szBuf, sizeof(szBuf)-1, 0, (struct sockaddr *)&m_SAddr_Server, &size );
			}

			if( recvsize == SOCKET_ERROR ) {
if( m_bServer ) {
DEBUGOUT( "FD_READ failed. Server [%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
} else {
DEBUGOUT( "FD_READ failed. Client [%s]\n", SocketErrorDump( ::WSAGetLastError() ) );
}
			} else if( recvsize > 0 ) {
				szBuf[recvsize] = '\0';

				if( m_hWndChat && ::IsWindow( m_hWndChat ) ) {
					COPYDATASTRUCT	cds;
					cds.dwData = 0;
					cds.lpData = (void*)szBuf;
					cds.cbData = ::strlen(szBuf)+1; //  �I�[��NULL������
					//  �����񑗐M
					::SendMessage( m_hWndChat, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds );
				}
			}
			break;
			}
		default:
DEBUGOUT( "Unknown message.\n" );
			break;
	}

	return	0L;
}

static	char*	SocketErrorDump( int eno )
{
	switch( eno ) {
	case	0:			return	"No error";

#if	defined(_DEBUG)||defined(_DEBUGOUT)
	case	WSAEINTR:		return	"Interrupted system call";
	case	WSAEBADF:		return	"Bad file number";
	case	WSAEACCES:		return	"Permission denied";
	case	WSAEFAULT:		return	"Bad address";
	case	WSAEINVAL:		return	"Invalid argument";
	case	WSAEMFILE:		return	"Too many open sockets";

	case	WSAEWOULDBLOCK:		return	"Operation would block";
	case	WSAEINPROGRESS:		return	"Operation now in progress";
	case	WSAEALREADY:		return	"Operation already in progress";
	case	WSAENOTSOCK:		return	"Socket operation on non-socket";
	case	WSAEDESTADDRREQ:	return	"Destination address required";
	case	WSAEMSGSIZE:		return	"Message too long";
	case	WSAEPROTOTYPE:		return	"Protocol wrong type for socket";
	case	WSAENOPROTOOPT:		return	"Bad protocol option";
	case	WSAEPROTONOSUPPORT:	return	"Protocol not supported";
	case	WSAESOCKTNOSUPPORT:	return	"Socket type not supported";
	case	WSAEOPNOTSUPP:		return	"Operation not supported on socket";
	case	WSAEPFNOSUPPORT:	return	"Protocol family not supported";
	case	WSAEAFNOSUPPORT:	return	"Address family not supported";
	case	WSAEADDRINUSE:		return	"Address already in use";
	case	WSAEADDRNOTAVAIL:	return	"Can't assign requested address";
	case	WSAENETDOWN:		return	"Network is down";
	case	WSAENETUNREACH:		return	"Network is unreachable";
	case	WSAENETRESET:		return	"Net connection reset";
	case	WSAECONNABORTED:	return	"Software caused connection abort";
	case	WSAECONNRESET:		return	"Connection reset by peer";
	case	WSAENOBUFS:		return	"No buffer space available";
	case	WSAEISCONN:		return	"Socket is already connected";
	case	WSAENOTCONN:		return	"Socket is not connected";
	case	WSAESHUTDOWN:		return	"Can't send after socket shutdown";
	case	WSAETOOMANYREFS:	return	"Too many references, can't splice";
	case	WSAETIMEDOUT:		return	"Connection timed out";
	case	WSAECONNREFUSED:	return	"Connection refused";
	case	WSAELOOP:		return	"Too many levels of symbolic links";
	case	WSAENAMETOOLONG:	return	"File name too long";
	case	WSAEHOSTDOWN:		return	"Host is down";
	case	WSAEHOSTUNREACH:	return	"No route to host";
	case	WSAENOTEMPTY:		return	"Directory not empty";
	case	WSAEPROCLIM:		return	"Too many processes";
	case	WSAEUSERS:		return	"Too many users";
	case	WSAEDQUOT:		return	"Disc quota exceeded";
	case	WSAESTALE:		return	"Stale NFS file handle";
	case	WSAEREMOTE:		return	"Too many levels of remote in path";

	case	WSAEDISCON:		return	"Graceful shutdown in progress";

	case	WSASYSNOTREADY:		return	"Network system is unavailable";
	case	WSAVERNOTSUPPORTED:	return	"Winsock version out of range";
	case	WSANOTINITIALISED:	return	"WSAStartup not yet called";

	case	WSAHOST_NOT_FOUND:	return	"Host not found";

	case	WSATRY_AGAIN:		return	"WSATRY_AGAIN";

	case	WSANO_RECOVERY:		return	"WSANO_RECOVERY";

	case	WSANO_DATA:		return	"No host data of that type was found";
#endif
	default:			return	"Unknown";
		break;
	}
	return	"";
}

