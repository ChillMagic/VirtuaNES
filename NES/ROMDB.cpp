﻿//
// NES ROMDB class
//
#include <cstdio>
#include <cstdlib>

#include "Typedef.h"
#include "Macro.h"

#include "DebugOut.h"
#include "AppWrapper.h"
#include "Pathlib.h"
#include "Crclib.h"

#include "Archive.h"

#include "ROMDB.h"

#ifdef _WIN32
#include <mbstring.h>
#endif

ROMDATABASE	romdatabase;

//
// ROM DATABASE (NESToy&NNNesterJ database)
//
INT	ROMDATABASE::HeaderCheck( NESHEADER& hdr, DWORD crcall, DWORD crc, ROMDB& data )
{
	if( m_DataBaseList.empty() ) {
		LoadDatabase();
	}

	if( m_DataBaseList.empty() )
		return	-2;	// データベースが無い

	map<DWORD, ROMDB, ROMDBCMP>::iterator it = m_DataBaseList.find( crcall );

	if( it == m_DataBaseList.end() )
		return	-1;	// データベースに無い

	data = (*it).second;

	// 一応チェック
	if( data.crcall == crcall || (data.crc == crc && data.crc) ) {
		if( hdr.control1 == data.control1 && hdr.control2 == data.control2 ) {
			return	0;	// 完全適合
		}
	}
	return	1;	// CRCは一致したがヘッダが違う
}

BOOL	ROMDATABASE::HeaderCorrect( NESHEADER& hdr, DWORD crcall, DWORD crc )
{
	if( m_DataBaseList.empty() ) {
		LoadDatabase();
	}

	if( m_DataBaseList.empty() )
		return	FALSE;	// データベースが無い

	map<DWORD, ROMDB, ROMDBCMP>::iterator it = m_DataBaseList.find( crcall );

	if( it == m_DataBaseList.end() )
		return	FALSE;	// データベースに無い

	ROMDB	data = (*it).second;

	// 一応チェック
	if( data.crcall == crcall || (data.crc == crc && data.crc) ) {
		hdr.control1 = data.control1;
		hdr.control2 = data.control2;
		for( INT i = 0; i < 8; i++ ) {
			hdr.reserved[i] = 0;
		}
		return	TRUE;
	}
	return	FALSE;
}

void	ROMDATABASE::LoadDatabase()
{
#ifdef _WIN32
FILE*	fp = NULL;
CHAR	buf[512];
const UCHAR seps[] = ";\n\0";	// セパレータ
ROMDB	db;

DEBUGOUT( "Database loading...\n" );

	string	Path = CPathlib::MakePathExt( AppWrapper::GetModulePath(), "nesromdb", "dat" );

DEBUGOUT( "File:%s\n", Path.c_str() );

	m_DataBaseList.clear();

	if( (fp = fopen( Path.c_str(), "r" )) ) {
		while( fgets( buf, 512, fp ) ) {
			if( buf[0] == ';' ) {	// コメントフィールドとみなす
				continue;
			}

			CHAR*	pToken;

			// ALL CRC
			if( !(pToken = (CHAR*)_mbstok( (UCHAR*)buf, seps )) )
				continue;
			db.crcall = strtoul( pToken, NULL, 16 );
			// PRG CRC
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.crc = strtoul( pToken, NULL, 16 );

			// Title
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.title = pToken;

			// Control 1
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.control1 = atoi( pToken );
			// Control 2
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.control2 = atoi( pToken );

			// PRG SIZE
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.prg_size = atoi( pToken );
			// CHR SIZE
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.chr_size = atoi( pToken );

			// Country
			if( !(pToken = (CHAR*)_mbstok( NULL, seps )) )
				continue;
			db.country = pToken;

			db.bNTSC = TRUE;
			// Europe (PAL???)
			if( strcmp( pToken, "E"   ) == 0
			 || strcmp( pToken, "Fra" ) == 0
			 || strcmp( pToken, "Ger" ) == 0
			 || strcmp( pToken, "Spa" ) == 0
			 || strcmp( pToken, "Swe" ) == 0
			 || strcmp( pToken, "Ita" ) == 0
			 || strcmp( pToken, "Aus" ) == 0 ) {
				db.bNTSC = FALSE;
			}

			// Manufacturer
			if( pToken = (CHAR*)_mbstok( NULL, seps ) ) {
				db.manufacturer = pToken;
			} else {
				db.manufacturer.erase( db.manufacturer.begin(), db.manufacturer.end() );
			}

			// Sale date
			if( pToken = (CHAR*)_mbstok( NULL, seps ) ) {
				db.saledate = pToken;
			} else {
				db.saledate.erase( db.saledate.begin(), db.saledate.end() );
			}

			// Price
			if( pToken = (CHAR*)_mbstok( NULL, seps ) ) {
				db.price = pToken;
			} else {
				db.price.erase( db.price.begin(), db.price.end() );
			}

			// Genre
			if( pToken = (CHAR*)_mbstok( NULL, seps ) ) {
				db.genre = pToken;
			} else {
				db.genre.erase( db.genre.begin(), db.genre.end() );
			}

			m_DataBaseList[db.crcall] = db;
		}
		FCLOSE( fp );
	} else {
DEBUGOUT( "Database file not found.\n" );
	}
#endif
}

