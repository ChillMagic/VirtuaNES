//
// DirectDraw class
//
#ifndef	__DIRECTDRAW_INCLUDED__
#define	__DIRECTDRAW_INCLUDED__

#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <objbase.h>
#include <mmsystem.h>

#include <vector>
using namespace std;

#define DIRECTDRAW_VERSION	0x0700
#include <ddraw.h>
#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "macro.h"

class	CDirectDraw
{
public:
	// �p�u���b�N�����o�ϐ�
	typedef	struct	tagDISPLAYMODE {
		DWORD		dwWidth;
		DWORD		dwHeight;
		DWORD		dwDepth;
		DWORD		dwRate;
	} DISPLAYMODE, *LPDISPLAYMODE;

	typedef	struct	tagPALBUF {
		BYTE		r;
		BYTE		g;
		BYTE		b;
	} PALBUF, *LPPALBUF;

	// ���p�\�ȃf�B�X�v���C���[�h
	enum { DD_DISPLAYMODEMAX = 512 };

	INT		m_DisplayModeNum;	// �f�B�X�v���C���[�h��
	DISPLAYMODE	m_DisplayModeBuf[DD_DISPLAYMODEMAX];

	// Screen size
	enum { SCREEN_WIDTH = 256, SCREEN_HEIGHT = 240 };

	// Render screen size
	enum { RENDER_WIDTH = SCREEN_WIDTH+16, RENDER_HEIGHT = SCREEN_HEIGHT };

	// Delta screen size
	enum { DELTA_WIDTH = SCREEN_WIDTH, DELTA_HEIGHT = SCREEN_HEIGHT+6 };

	// Filter
	enum {	BLTFILTER_NONE = 0,
		BLTFILTER_2XSAI,
		BLTFILTER_SUPER2XSAI,
		BLTFILTER_SUPEREAGLE,
		BLTFILTER_SCALE2X,
		BLTFILTER_HQ2X,
		BLTFILTER_LQ2X,
	};

	// �p�u���b�N�����o�֐�
	CDirectDraw();
	virtual ~CDirectDraw();

	BOOL	InitialDDraw( HWND hWnd );
	void	ReleaseDDraw();

	BOOL	InitialSurface( BOOL bScreenMode );
	BOOL	ReleaseSurface();
	BOOL	RestoreSurface();

	BOOL	BeginDisplayChange();
	BOOL	EndDisplayChange();
	BOOL	OnChangeDisplayMode();

	// Display���[�h
	INT	GetDisplayModeNum()	{ return m_DisplayModes.size(); }
	void	SetDisplayMode( DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, DWORD dwRate );
	void	GetDisplayMode( DWORD& dwWidth, DWORD& dwHeight, DWORD& dwDepth, DWORD& dwRate );
	BOOL	GetDisplayMode( INT no, DWORD& dwWidth, DWORD& dwHeight, DWORD& dwDepth, DWORD& dwRate );
	INT	GetMatchDisplayMode( DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, DWORD dwRate );
	BOOL	IsNowDisplayMode( DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, DWORD dwRate );

	BOOL	CalcPaletteTable();
	void	SetPaletteTable( LPBYTE pal );
	void	SetPaletteTable( RGBQUAD* pal );
	void	GetPaletteTable( RGBQUAD* pal );
	void	SetPaletteFile( LPCTSTR fname );

	BOOL	SetFullScreenGDI( BOOL bMode );

	void	SetUseHEL( BOOL bUseHEL ) {
		m_bUseHEL = bUseHEL;
		m_bDeltaUpdate = TRUE;
	}
	void	SetSystemMemory( BOOL bSystemMemory ) {
		m_bSystemMemory = bSystemMemory;
		m_bDeltaUpdate = TRUE;
	}
	void	SetScreenMode( BOOL bScreenMode ) {
		m_bScreenMode = bScreenMode;
		m_bDeltaUpdate = TRUE;
	}
	void	SetFlipMode( BOOL bFlip ) {
		m_bFlip = bFlip;
	}
	void	SetAspectMode( BOOL bAspect ) {
		m_bAspect = bAspect;
	}
	void	SetAllLineMode( BOOL bAllLine ) {
		m_bAllLine = bAllLine;
	}
	void	SetMaxZoom( BOOL bZoom ) {
		m_bMaxZoom = bZoom;
	}
	void	SetDoubleSize( BOOL bDoubleSize ) {
		m_bDoubleSize = bDoubleSize;
		m_bDeltaUpdate = TRUE;
	}
	void	SetTVFrameMode( BOOL bTVFrame ) {
		m_bTVFrameMode = bTVFrame;
	}
	void	SetScanlineMode( BOOL bScanline ) {
		m_bScanlineMode = bScanline;
		m_bDeltaUpdate = TRUE;
	}
	void	SetScanlineColor( INT nScanlineColor ) {
		m_nScanlineColor = nScanlineColor;
	}

	void	SetZapperMode( BOOL bZapper ) {
		m_bZapper = bZapper;
	}
	void	SetZapperDrawMode( BOOL bDraw ) {
		m_bZapperDraw = bDraw;
	}

	void	SetWindowVSyncMode( BOOL bVSync ) {
		m_bWindowVSync = bVSync;
	}

	void	SetGraphicsFilter( INT nFilter ) {
		m_nBltFilter = nFilter;
		m_bDeltaUpdate = TRUE;
	}

	BOOL	GetUseHEL()		{ return m_bUseHEL; }
	BOOL	GetSystemMemory()	{ return m_bSystemMemory; }
	BOOL	GetScreenMode()		{ return m_bScreenMode; }
	BOOL	GetFlipMode()		{ return m_bFlip; }
	BOOL	GetAspectMode()		{ return m_bAspect; }
	BOOL	GetAllLineMode()	{ return m_bAllLine; }
	BOOL	GetMaxZoom()		{ return m_bMaxZoom; }
	BOOL	GetDoubleSize()		{ return m_bDoubleSize; }
	BOOL	GetTVFrameMode()	{ return m_bTVFrameMode; }
	BOOL	GetScanlineMode()	{ return m_bScanlineMode; }
	INT	GetScanlineColor()	{ return m_nScanlineColor; }
	BOOL	GetZapperMode()		{ return m_bZapper; }
	BOOL	GetZapperDrawMode()	{ return m_bZapperDraw; }

	BOOL	GetWindowVSyncMode()	{ return m_bWindowVSync; }

	INT	GetGraphicsFilter()	{ return m_nBltFilter; }

	LPBYTE	GetRenderScreen()	{ return m_lpRender; }
	LPBYTE	GetLineColormode()	{ return m_LineColormode; }

	// For Zapper
	BYTE	GetZapperHit();
	void	GetZapperPos( LONG& x, LONG& y );
	void	SetZapperPos( LONG x, LONG y );

	void	SetInfoString( LPCSTR str );
	void	SetMessageString( LPCSTR str );

	void	RealizePalette();

	void	OnScreenDraw();
	void	SetPaletteMode( INT nMode, BOOL bMono );
	void	GetPaletteData( RGBQUAD* rgb );
	void	GetPaletteData2( RGBQUAD* rgb );

	void	SetDiskAccessLamp( BOOL bAccess ) {
		m_bDiskAccessLamp = bAccess;
	}

	void	Blt();
	void	Flip();

	// MMX
	BOOL	IsMMX() { return m_bMMX; }


	BYTE	GetPixel( INT x, INT y );

protected:
	// �v���e�N�g�����o�ϐ�

	// General
	HWND	m_hWnd;			// Window handle
	BOOL	m_bChangeMode;		// Screen Mode changing flag
	BOOL	m_bDraw;		// Drawing flag
	BOOL	m_bNoRestore;

	BOOL	m_bMessage;		// Message display?
	DWORD	m_dwMessageTime;	// Message display times

	BOOL	m_bMMX;			// Existence of MMX technology.

	// Options
	BOOL	m_bUseHEL;		// HAL���g�킸HEL���g�p
	BOOL	m_bSystemMemory;	// �T�[�t�F�X�ɃV�X�e�����������g�p

	BOOL	m_bScreenMode;		// FALSE:Window  TRUE:Fullscreen
	BOOL	m_bFlip;		// �t���b�v�g�p
	BOOL	m_bGDI;			// GDI
	BOOL	m_bAspect;		// TV�A�X�y�N�g�␳
	BOOL	m_bAllLine;		// �S���C���\��
	BOOL	m_bMaxZoom;		// ��ʑS�̂܂Ŋg��
	BOOL	m_bDoubleSize;		// �Q�{�T�C�Y�����_�����O
	BOOL	m_bTVFrameMode;		// TV�g�\��
	BOOL	m_bScanlineMode;	// �X�L�������C�����[�h
	INT	m_nScanlineColor;	// �X�L�������C���J���[
	BOOL	m_bZapper;		// Zapper
	BOOL	m_bZapperDraw;		// Zapper Sight drawing

	BOOL	m_bWindowVSync;		// Wait for VSync(Window mode)

	BOOL	m_bForceWrite;		// ��ɏ㏑���`��
	INT	m_nBltFilter;		// Blit Filter

	// ���p�\�ȃf�B�X�v���C���[�h
	std::vector<DISPLAYMODE> m_DisplayModes;

	// �t���X�N���[���f�B�X�v���C���[�h
	DWORD	m_dwDisplayWidth;
	DWORD	m_dwDisplayHeight;
	DWORD	m_dwDisplayDepth;
	DWORD	m_dwDisplayRate;

	// DLL dynamic load
	HINSTANCE	m_hDDraw;	// DLL Instance handle

	// DirectDraw object
	LPDIRECTDRAW7		m_lpDD;		// DirectDraw Object
	LPDIRECTDRAWSURFACE7	m_lpDDPrimary;	// PrimarySurface
	LPDIRECTDRAWSURFACE7	m_lpDDBack;	// BackSurface
	LPDIRECTDRAWSURFACE7	m_lpDDRender;	// RenderSurface
	LPDIRECTDRAWSURFACE7	m_lpDDRender2;	// RenderSurface2
	LPDIRECTDRAWSURFACE7	m_lpDDAscii;	// AsciiSurface
	LPDIRECTDRAWSURFACE7	m_lpDDZapper;	// ZapperSurface
	LPDIRECTDRAWSURFACE7	m_lpDDTV;	// TV�g(^^;
	LPDIRECTDRAWCLIPPER	m_lpDDClipper;	// Clipper
	LPDIRECTDRAWCLIPPER	m_lpDDClipper2;	// Render window Clipper
	LPDIRECTDRAWPALETTE	m_lpDDPalette;	// DirectDraw Palette

	LPBYTE			m_lpRender;
	LPBYTE			m_lpRenderDelta;
	BYTE			m_LineColormode[RENDER_HEIGHT];

	BOOL			m_bDeltaUpdate;

	// �p���b�g
	INT	m_nPaletteMode;
	BOOL	m_bMonoMode;
	BOOL	m_bPaletteUpdate;	// Palette Update?

	static	PALBUF	m_PalDefault[64];	// �f�t�H���g�p���b�g
	PALBUF		m_PaletteBuf[64];	// �p���b�g�o�b�t�@

	typedef	struct	tagLOGPAL {
		WORD		palVersion;
		WORD		palNumEntries;
		PALETTEENTRY	pe[256];
	} LOGPAL, *LPLOGPAL;

	HPALETTE	m_hPalette;	// Windows GDI Palette handle
	LOGPAL		m_logPalette;	// Windows GDI Palette

	// 256�F���[�h�p
	RGBQUAD	m_cpPalette[8][64*2];	// Color
	RGBQUAD	m_mpPalette[8][64*2];	// Monochrome

	// �s�N�Z���t�H�[�}�b�g�ɕϊ������p���b�g
	DWORD	m_cnPalette[8][256];	// Color
	DWORD	m_csPalette[8][256];	// Color/Scanline
	DWORD	m_mnPalette[8][256];	// Monochrome
	DWORD	m_msPalette[8][256];	// Monochrome/Scanline

	// 2xSaI mmx�p��RGB555�p���b�g
	DWORD	m_cfPalette[8][256];	// Color
	DWORD	m_mfPalette[8][256];	// Monochrome

	// For Zapper
	LONG	m_ZapperPosX, m_ZapperPosY;

	// For Infomation&Message
	enum	{ INFOSTR_SIZE = 64 };

	CHAR	m_szInfo[INFOSTR_SIZE+1];
	CHAR	m_szMess[INFOSTR_SIZE+1];

	// For DiskAccessLamp
	BOOL	m_bDiskAccessLamp;

	// �v���e�N�g�����o�֐�
	static	HRESULT	WINAPI	EnumModesCallback( LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext );

	void	RenderString( INT x, INT y, LPCSTR str );

	BOOL	RestoreSurfaceSub( LPDIRECTDRAWSURFACE7 lpSurface );
	void	GetBitMask( DWORD val, int& shift, int& bits );

	void	SetLZSSChar( LPBYTE lpLZ, LPDIRECTDRAWSURFACE7 lpDDSurface );

	// Blitters
	typedef	void	(CDirectDraw::*BLTFUNC)(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

	static	BLTFUNC	NormalBltTable[];
	static	BLTFUNC	ScanlineBltTable[];
	static	BLTFUNC	DoubleBltTable[];
	static	BLTFUNC	DoubleScanlineBltTable[];
	static	BLTFUNC	nx2xSaIBltTable[];
	static	BLTFUNC	nxSuper2xSaIBltTable[];
	static	BLTFUNC	nxSuperEagleBltTable[];
	static	BLTFUNC	nxScale2xBltTable[];
	static	BLTFUNC	nxHq2xBltTable[];
	static	BLTFUNC	nxLq2xBltTable[];

	// ��ʁc
	void	Render8bpp_Normal(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render16bpp_Normal(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render24bpp_Normal(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render32bpp_Normal(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

	void	Render8bpp_Scanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render16bpp_Scanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render24bpp_Scanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render32bpp_Scanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

	void	Render8bpp_Double(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render16bpp_Double(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render24bpp_Double(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render32bpp_Double(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

	void	Render8bpp_DoubleScanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render16bpp_DoubleScanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render24bpp_DoubleScanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	Render32bpp_DoubleScanline(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

	// �v�������_�p
	void	Render16bpp( LPBYTE lpSrc, LPBYTE lpDst );
	void	Render16bppPrefilter( LPBYTE lpSrc, LPBYTE lpDst );
	void	Render32bpp( LPBYTE lpSrc, LPBYTE lpDst );

	// Effects
	void	nx_2xSaI_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_2xSaI_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_Super2xSaI_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_Super2xSaI_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_SuperEagle_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_SuperEagle_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_Scale2x_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_Scale2x_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_hq2x_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_hq2x_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_lq2x_16bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);
	void	nx_lq2x_32bpp(LPBYTE,LPBYTE,DDSURFACEDESC2&,BOOL);

private:
	// �v���C�x�[�g�����o�ϐ�
	// �v���C�x�[�g�����o�֐�
};

extern	CDirectDraw	DirectDraw;

#endif	// !__DIRECTDRAW_INCLUDED__
