//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      NES APU core                                                    //
//                                                           Norix      //
//                                               written     2001/02/22 //
//                                               last modify ----/--/-- //
//////////////////////////////////////////////////////////////////////////
#ifndef	__APU_INCLUDED__
#define	__APU_INCLUDED__

#include "WindowsSDKImport.h"
#include <cmath>

#include "Typedef.h"
#include "Macro.h"

#include "ApuEx/APU_INTERNAL.h"
#include "ApuEx/APU_VRC6.h"
#include "ApuEx/APU_VRC7.h"
#include "ApuEx/APU_MMC5.h"
#include "ApuEx/APU_FDS.h"
#include "ApuEx/APU_N106.h"
#include "ApuEx/APU_FME7.h"

//#define	QUEUE_LENGTH	4096
#define	QUEUE_LENGTH	8192

// class prototype
class	NES;

class	APU
{
public:
	APU( NES* parent );
	virtual	~APU();

	void	SoundSetup();
	void	SelectExSound( BYTE data );

	BOOL	SetChannelMute( INT nCH ) { m_bMute[nCH] = !m_bMute[nCH]; return m_bMute[nCH]; }

	void	QueueClear();

	void	Reset();
	BYTE	Read( WORD addr );
	void	Write( WORD addr, BYTE data );
	BYTE	ExRead( WORD addr );
	void	ExWrite( WORD addr, BYTE data );

	void	Sync();
	void	SyncDPCM( INT cycles );

	void	Process( LPBYTE lpBuffer, DWORD dwSize );

	// For NSF player
	INT	GetChannelFrequency( INT ch );
	LPSHORT	GetSoundBuffer() { return m_SoundBuffer; }

	// For State
	void	GetFrameIRQ( INT& Cycle, BYTE& Count, BYTE& Type, BYTE& IRQ, BYTE& Occur ) {
		internal.GetFrameIRQ( Cycle, Count, Type, IRQ, Occur );
	}

	void	SetFrameIRQ( INT Cycle, BYTE Count, BYTE Type, BYTE IRQ, BYTE Occur ) {
		internal.SetFrameIRQ( Cycle, Count, Type, IRQ, Occur );
	}

	void	SaveState( LPBYTE p );
	void	LoadState( LPBYTE p );
protected:
	typedef	struct {
		INT	time;
		WORD	addr;
		BYTE	data;
		BYTE	reserved;
	} QUEUEDATA, *LPQUEUEDATA;

	typedef	struct {
		INT		rdptr;
		INT		wrptr;
		QUEUEDATA	data[QUEUE_LENGTH];
	} QUEUE, *LPQUEUE;

	void	SetQueue( INT writetime, WORD addr, BYTE data );
	BOOL	GetQueue( INT writetime, QUEUEDATA& ret );

	void	SetExQueue( INT writetime, WORD addr, BYTE data );
	BOOL	GetExQueue( INT writetime, QUEUEDATA& ret );

	void	QueueFlush();

	void	WriteProcess( WORD addr, BYTE data );
	void	WriteExProcess( WORD addr, BYTE data );

	NES*	nes;

	QUEUE	queue;
	QUEUE	exqueue;

	BYTE	exsound_select;

	double	elapsed_time;
//	INT	elapsed_time;

	// Filter
	INT	last_data, last_diff;
	INT	lowpass_filter[4];

	// Sound core
	APU_INTERNAL	internal;
	APU_VRC6	vrc6;
	APU_VRC7	vrc7;
	APU_MMC5	mmc5;
	APU_FDS		fds;
	APU_N106	n106;
	APU_FME7	fme7;

	// Channel mute
	BOOL	m_bMute[16];

	// おまけ
	SHORT	m_SoundBuffer[0x100];
private:
};

#endif	// !__APU_INCLUDED__
