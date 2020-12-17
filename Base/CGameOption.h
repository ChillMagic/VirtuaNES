#pragma once
#include "Base/Typedef.h"

// 個別ゲームオプション
class	CGameOption
{
public:
	// for Cartridge
	void	Load(DWORD crc);
	void	Save(LPCSTR name, DWORD crc);
	// for FDS
	void	Load(DWORD gid, DWORD mid);
	void	Save(LPCSTR name, DWORD gid, DWORD mid);

	// Default保存
	INT	defRenderMethod;
	INT	defIRQtype;
	BOOL	defFrameIRQ;
	BOOL	defVideoMode;

	// データ
	INT	nRenderMethod;
	INT	nIRQtype;
	BOOL	bFrameIRQ;
	BOOL	bVideoMode;
protected:
private:
};
