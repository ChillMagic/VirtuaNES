
#include "APIWrapper.h"

static bool implCreateDirectory(const char* path, void* security_attributes);
static short implGetAsyncKeyState(int key);

void APIWrapper::CreateDirectory(const char* path, void* security_attributes)
{
	implCreateDirectory(path, security_attributes);
}

short APIWrapper::GetAsyncKeyState(int key)
{
	return implGetAsyncKeyState(key);
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

short APIWrapper::GetAsyncKeyStateLeftButton()
{
	return GetAsyncKeyState(VK_LBUTTON);
}

short APIWrapper::GetAsyncKeyStateRightButton()
{
	return GetAsyncKeyState(VK_RBUTTON);
}

static bool implCreateDirectory(const char* path, void* security_attributes)
{
	return CreateDirectory(path, (LPSECURITY_ATTRIBUTES)security_attributes);
}

short implGetAsyncKeyState(int key)
{
	return GetAsyncKeyState(key);
}

