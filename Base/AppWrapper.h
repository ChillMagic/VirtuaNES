#pragma once
#include "Base/Typedef.h"

class AppWrapper {
public:
	static LPCSTR GetErrorString(INT nID);
	static LPCSTR GetModulePath();
};

extern	CHAR	szErrorString[256];
