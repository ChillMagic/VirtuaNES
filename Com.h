//
// COM利用サポートクラス
//
#ifndef	__CCOM_INCLUDED__
#define	__CCOM_INCLUDED__

#include "WindowsSDKImport.h"

class	COM
{
public:
	static	LRESULT	AddRef();
	static	void	Release();

protected:
	static	INT	m_nRefCount;
};

#endif	// !__CCOM_INCLUDED__

