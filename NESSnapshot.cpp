
#include "VirtuaNESres.h"
#include "Base/AppWrapper.h"
#include "Base/ConfigWrapper.h"
#include "Base/DebugOut.h"
#include "Base/Typedef.h"

#include "NES/Nes.h"
#include "NES/ROM.h"
#include "NES/PPU.h"

#include "DirectDraw.h"
#include "Base/Pathlib.h"
#include "Pngwrite.h"


BOOL	NES::Snapshot()
{
	FILE* fp = NULL;

	try {
		SYSTEMTIME	now;
		::GetLocalTime(&now);

		CHAR	name[_MAX_PATH];

		if (!ConfigWrapper::GetCCfgEmulator().bPNGsnapshot) {
			sprintf(name, "%s %04d%02d%02d%02d%02d%02d%01d.bmp", rom->GetRomName(),
				now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds / 100);
		}
		else {
			sprintf(name, "%s %04d%02d%02d%02d%02d%02d%01d.png", rom->GetRomName(),
				now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds / 100);
		}

		string	pathstr, tempstr;
		if (ConfigWrapper::GetCCfgPath().bSnapshotPath) {
			pathstr = CPathlib::CreatePath(AppWrapper::GetModulePath(), ConfigWrapper::GetCCfgPath().szSnapshotPath);
			::CreateDirectory(pathstr.c_str(), NULL);
		}
		else {
			pathstr = rom->GetRomPath();
		}
		tempstr = CPathlib::MakePath(pathstr.c_str(), name);
		DEBUGOUT("Snapshot: %s\n", tempstr.c_str());

		if (!ConfigWrapper::GetCCfgEmulator().bPNGsnapshot) {
			if (!(fp = ::fopen(tempstr.c_str(), "wb"))) {
				// xxx ファイルを開けません
				LPCSTR	szErrStr = AppWrapper::GetErrorString(IDS_ERROR_OPEN);
				sprintf(szErrorString, szErrStr, tempstr.c_str());
				throw	szErrorString;
			}

			LPBYTE	lpScn = ppu->GetScreenPtr();

			BITMAPFILEHEADER bfh;
			BITMAPINFOHEADER bih;
			RGBQUAD		 rgb[256];

			ZEROMEMORY(&bfh, sizeof(bfh));
			ZEROMEMORY(&bih, sizeof(bih));
			ZEROMEMORY(rgb, sizeof(rgb));

			bfh.bfType = 0x4D42;	// 'BM'
			bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256;
			bfh.bfSize = bfh.bfOffBits + 256 * 240;

			bih.biSize = sizeof(bih);
			bih.biWidth = 256;
			bih.biHeight = 240;
			bih.biPlanes = 1;
			bih.biBitCount = 8;
			bih.biCompression = BI_RGB;
			bih.biSizeImage = 0;
			bih.biXPelsPerMeter = 0;
			bih.biYPelsPerMeter = 0;
			bih.biClrUsed = 256;
			bih.biClrImportant = 0;

			DirectDraw.GetPaletteData(rgb);

			if (::fwrite(&bfh, sizeof(bfh), 1, fp) != 1) {
				// ファイルの書き込みに失敗しました
				throw	AppWrapper::GetErrorString(IDS_ERROR_WRITE);
			}
			if (::fwrite(&bih, sizeof(bih), 1, fp) != 1) {
				// ファイルの書き込みに失敗しました
				throw	AppWrapper::GetErrorString(IDS_ERROR_WRITE);
			}
			if (::fwrite(&rgb, sizeof(rgb), 1, fp) != 1) {
				// ファイルの書き込みに失敗しました
				throw	AppWrapper::GetErrorString(IDS_ERROR_WRITE);
			}

			lpScn += 8;
			for (INT i = 239; i >= 0; i--) {
				if (::fwrite(&lpScn[(256 + 16) * i], 256, 1, fp) != 1) {
					// ファイルの書き込みに失敗しました
					throw	AppWrapper::GetErrorString(IDS_ERROR_WRITE);
				}
			}

			FCLOSE(fp);
		}
		else {
			LPBYTE	lpScn = ppu->GetScreenPtr();
			RGBQUAD		 rgb[256];
			ZEROMEMORY(rgb, sizeof(rgb));
			DirectDraw.GetPaletteData(rgb);

			PNGWRITE png;

			png.Write(tempstr.c_str(), 256, 240, rgb, lpScn + 8, CDirectDraw::RENDER_WIDTH);
		}
	}
	catch (CHAR* str) {
		DEBUGOUT("Snapshot error.\n");
		FCLOSE(fp);
		throw	str;
#ifndef	_DEBUG
	}
	catch (...) {
		DEBUGOUT("Snapshot error.\n");
		FCLOSE(fp);
		// 不明なエラーが発生しました
		throw	AppWrapper::GetErrorString(IDS_ERROR_UNKNOWN);
#endif
	}

	return	TRUE;
}
