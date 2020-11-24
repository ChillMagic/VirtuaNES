//
// DirectSound class
//
#ifndef	__DIRECTSOUND_INCLUDED__
#define	__DIRECTSOUND_INCLUDED__

#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#define DIRECTSOUND_VERSION	0x0700
#include <dsound.h>

#include "extsoundfile.h"

#include "typedef.h"
#include "macro.h"

class	CWaveData
{
public:
	CWaveData();
	virtual	~CWaveData();

	BOOL		Load( LPCSTR szFileName );
	void		Free();

	DWORD		GetSize();
	WAVEFORMATEX*	GetFormat();
	LPVOID		GetData();
protected:
	LPVOID		m_pBuffer;

	WAVEFORMATEX*	m_pwfex;
	DWORD		m_dwSize;

	LPVOID		m_pData;

private:
};

class	CDirectSound
{
public:
	// �p�u���b�N�����o�ϐ�
	typedef	struct	tagSAMPLERATE {
		DWORD	Rate;
		DWORD	Bits;
	} SAMPLERATE, *LPSAMPLERATE;

	SAMPLERATE		m_SampleRate;		// ���݃T���v�����O���[�g
	INT			m_BufferSize;		// �o�b�t�@�T�C�Y(�t���[����)
	static	SAMPLERATE	m_SampleRateTable[];	// �T���v�����O���[�g�e�[�u��
	static	INT		m_BufferSizeTable[];	// �o�b�t�@�T�C�Y�e�[�u��

	// �p�u���b�N�����o�֐�
	CDirectSound();
	virtual ~CDirectSound();

	BOOL	InitialDSound( HWND hWnd );
	void	ReleaseDSound();

	BOOL	InitialBuffer();
	void	ReleaseBuffer();

	BOOL	SetSamplingRate( DWORD rate, DWORD bits );
	void	GetSamplingRate( DWORD& rate, DWORD& bits );

	void	SetBufferSize( INT nSize ) { m_BufferSize = nSize; }
	INT	GetBufferSize()		   { return m_BufferSize; }

	BOOL	IsStreamPlaying() { return (m_bStreamPlay&&!m_bStreamPause); }
	void	StreamPlay();
	void	StreamStop();
	void	StreamPause();
	void	StreamResume();

	BOOL	GetStreamLockPosition( LPDWORD lpdwStart, LPDWORD lpdwSize );
	BOOL	StreamLock( DWORD dwWriteCursor, DWORD dwWriteBytes, LPVOID* lplpvPtr1, LPDWORD lpdwBytes1, LPVOID* lplpvPtr2, LPDWORD lpdwBytes2, DWORD dwFlags );
	BOOL	StreamUnlock( LPVOID lpvPtr1, DWORD dwBytes1, LPVOID lpvPtr2, DWORD dwBytes2 );

	BOOL	IsStreamPlay() { return m_bStreamPlay; }
	BOOL	IsStreamPause() { return m_bStreamPause; }

	// �O�������t�@�C���Ή�
	BOOL	LoadEsf( LPCSTR szFileName, INT no );
	BOOL	EsfPlay( INT no );
	BOOL	EsfPlayLoop( INT no );
	BOOL	EsfStop( INT no );
	void	EsfAllStop();
	BOOL	CreateESFBuffer( INT no, WAVEFORMATEX* pwfex, LPVOID pData, DWORD dwSize );
	void	ReleaseEsfBuffer();

protected:
	// �v���e�N�g�����o�ϐ�
	HWND	m_hWnd;		// Window handle

	LPDIRECTSOUND		m_lpDS;		// DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER	m_lpDSPrimary;	// �v���C�}���I�u�W�F�N�g

	LPDIRECTSOUNDBUFFER	m_lpDSStream;		// �X�g���[�~���O�I�u�W�F�N�g

	DWORD			m_dwDSBufferSize;
	DWORD			m_dwDSBlockSize;	// 1�u���b�N�̃T�C�Y
	DWORD			m_dwDSBlockNum;		// �u���b�N�̐�
	DWORD			m_dwDSLastBlock;	// �Ō�ɏ������񂾃u���b�N�ʒu

	volatile BOOL		m_bStreamPlay;	// �X�g���[���Đ����t���O
	volatile BOOL		m_bStreamPause;	// �X�g���[���|�[�Y�t���O

	// �O�������t�@�C���Ή�
	CWaveData		m_EsfWaveFile[ ESF_FILE_MAX ];
	LPDIRECTSOUNDBUFFER	m_pEsfDSBuffer[ ESF_FILE_MAX ];

	// �v���e�N�g�����o�֐�
private:
	// �v���C�x�[�g�����o�ϐ�
	// �v���C�x�[�g�����o�֐�
};

extern	CDirectSound	DirectSound;

#endif	// !__DIRECTSOUND_INCLUDED__
