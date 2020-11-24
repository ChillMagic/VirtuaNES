//
// �G�~�����[�^�X���b�h�N���X
//
#ifndef	__CEMUTHREAD_INCLUDED__
#define	__CEMUTHREAD_INCLUDED__

#define	WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
#include <deque>
#include <queue>
using namespace std;

#include "App.h"
#include "MMTimer.h"
#include "Config.h"
#include "WaveRec.h"

#include "typedef.h"
#include "macro.h"

#include "nes.h"
#include "mmu.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "pad.h"
#include "rom.h"
#include "mapper.h"

// Prototypes
// NetPlay Event
class	NETEV	{
public:
	INT	Event;
	DWORD	Param;
};
//class	NES;

class	CEmuThread
{
public:
	CEmuThread();
	~CEmuThread();

	// �C�x���g
	enum EMUEVENT {
		EV_EXIT = -1,
		EV_NONE = 0,
		EV_INITIAL,
		EV_PAUSE,
		EV_RESUME,
		// �ȉ���Event�Ŏg�p����
		EV_MESSAGE_OUT,		// ���b�Z�[�W�����o�͂��������Ɏg�p

		EV_FULLSCREEN_GDI,	// EventParam

		EV_EMUPAUSE,
		EV_ONEFRAME,
		EV_THROTTLE,
		EV_FRAMESKIP_AUTO,
		EV_FRAMESKIP_UP,
		EV_FRAMESKIP_DOWN,

		EV_HWRESET,
		EV_SWRESET,

		EV_NETPLAY_START,

		EV_STATE_LOAD,		// EventParam2
		EV_STATE_SAVE,		// EventParam2

		// For Disk system
		EV_DISK_COMMAND,	// EventParam
		// For ExController
		EV_EXCONTROLLER,	// EventParam
		// For Sound
		EV_SOUND_MUTE,		// EventParam

		// For Snapshot
		EV_SNAPSHOT,
		// For Movie
		EV_MOVIE_PLAY,		// EventParam
		EV_MOVIE_REC,		// EventParam
		EV_MOVIE_RECAPPEND,	// EventParam
		EV_MOVIE_STOP,		// EventParam

		// For Wave recording
		EV_WAVEREC_START,	// EventParam
		EV_WAVEREC_STOP,

		// For Tape recording
		EV_TAPE_PLAY,		// EventParam
		EV_TAPE_REC,		// EventParam
		EV_TAPE_STOP,

		// For Barcode
		EV_BARCODE,		// EventParam2

		// For TurboFile
		EV_TURBOFILE,		// EventParam

		// For Debugger
		EV_DEBUG_RUN,
		EV_DEBUG_BRAKE,
		EV_DEBUG_STEP,
		EV_DEBUG_COMMAND,	// EventParam
	};

	// ���샂�[�h
	enum {
		STATUS_NONE = 0,
		STATUS_RUN,
		STATUS_PAUSE,
	};

	// �f�o�b�K�R�}���h

	//
	void	SetPriority( INT nPriority );

	BOOL	Start( HWND hWnd, NES* nes );
	void	Stop();
	void	Pause();
	void	Resume();

	void	Event( EMUEVENT ev );
	void	EventParam( EMUEVENT ev, LONG Param );
	void	EventParam2( EMUEVENT ev, LONG Param, LONG Param2 );

	BOOL	IsRunning()	{ return (g_Status!=STATUS_NONE); }
	BOOL	IsPausing()	{ return (g_Status==STATUS_PAUSE); }

	BOOL	IsWaveRecord()	{ return g_WaveRec.IsWaveRecord(); }

	INT	GetDiskNo()	{ if( g_nes ) return g_nes->rom->GetDiskNo(); else return 0; }
	INT	GetExController() { if( g_nes ) return g_nes->pad->GetExController(); else return 0; }

	//
	NES*	GetNES()	{ return g_nes; }

protected:
	static	void	DiskCommand( BYTE cmd );
	static	BOOL	FrameInput();

	static	DWORD WINAPI	ThreadProc( LPVOID lpVoid );
	// �T�E���h�X�g���[�~���O�p
	static	void	StreamProcess( BOOL bPause );

	// �X���b�h�n���h����ID
		HANDLE	m_hThread;
		DWORD	m_dwThreadID;

	// This�|�C���^
	static	CEmuThread*	g_pThis;
	// �E�C���h�E�n���h��
	static	HWND	g_hWnd;
	// �G�~�����[�^�I�u�W�F�N�g�|�C���^
	static	NES*	g_nes;

	// Wave���R�[�_
	static	CWaveRec g_WaveRec;

	// �|�[�Y�J�E���g
		INT	m_nPauseCount;
	// �X�e�[�^�X
	static	INT	g_Status;

	// �X���b�h�C�x���g�ƃC�x���g�n���h��
	static	INT	g_Event;
	static	LONG	g_EventParam;
	static	LONG	g_EventParam2;
	static	HANDLE	g_hEvent;
	static	HANDLE	g_hEventAccept;

	// �X���b�h�v���C�I���e�B
		INT	m_nPriority;
	static	INT	g_PriorityTable[];

	// �G���[���b�Z�[�W
	static	CHAR	g_szErrorMessage[512];

	// �X�g�����O�e�[�u��
	static	LPCSTR	g_lpSoundMuteStringTable[];

	// NetPlay Event
	static	deque<NETEV>	NetEventQueue;
	static	string		strNetStateName;

private:
};

extern	CEmuThread	Emu;

#endif	// !__CEMUTHREAD_INCLUDED__

