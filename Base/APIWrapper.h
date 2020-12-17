#pragma once

class APIWrapper {
public:
#ifdef CreateDirectory
#undef CreateDirectory
#endif
#ifdef GetAsyncKeyState
#undef GetAsyncKeyState
#endif
#ifdef PathFindExtension
#undef PathFindExtension
#endif
	static void CreateDirectory(const char *path, void *security_attributes);
	static short GetAsyncKeyState(int key);
	static short GetAsyncKeyStateLeftButton();
	static short GetAsyncKeyStateRightButton();
	static char * PathFindExtension(const char *path);
	static int stricmp(const char *string1, const char *string2);
};
