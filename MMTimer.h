﻿//
// Multimedia timer support
//
#ifndef	__CMMTIMER_INCLUDED__
#define	__CMMTIMER_INCLUDED__

#include "WindowsSDKImport.h"
#include <mmsystem.h>
#include "Typedef.h"

class	CMMTimer
{
public:
	CMMTimer();
	~CMMTimer();

	static	SQWORD	GetMMTimer();
	static	FLOAT	CalcTimeDifference( SQWORD t0, SQWORD t1 );

protected:
private:
	static	BOOL	m_bInitialize;

	// 高分解能カウンタを利用出来るかどうかのフラグ
	static	BOOL	m_bHigh;
	// 高分解能カウンタ周波数
	static	SQWORD	m_hpFrequency;
};

#endif	// !__CMMTIMER_INCLUDED__
