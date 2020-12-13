#pragma once

class APIWrapper {
public:
#ifdef CreateDirectory
#undef CreateDirectory
#endif
#ifdef GetAsyncKeyState
#undef GetAsyncKeyState
#endif
	static void CreateDirectory(const char *path, void *security_attributes);
	static short GetAsyncKeyState(int key);
	static short GetAsyncKeyStateLeftButton();
	static short GetAsyncKeyStateRightButton();
};
