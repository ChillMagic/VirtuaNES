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
	static unsigned char* mbsncpy(unsigned char* dst, const unsigned char* src, size_t len);
	static unsigned char* mbsinc(const unsigned char* path);
	static int mbsnbicmp(unsigned char *str1, unsigned char *str2, size_t max_count);
	static unsigned char* mbstok(unsigned char *str, const unsigned char *delim);
};
