
#include "Base/APIWrapper.h"

static bool implCreateDirectory(const char* path, void* security_attributes);
static short implGetAsyncKeyState(int key);
static char* implPathFindExtension(const char* path);

void APIWrapper::CreateDirectory(const char* path, void* security_attributes)
{
	implCreateDirectory(path, security_attributes);
}

short APIWrapper::GetAsyncKeyState(int key)
{
	return implGetAsyncKeyState(key);
}

char* APIWrapper::PathFindExtension(const char* path) {
	return implPathFindExtension(path);
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>

short APIWrapper::GetAsyncKeyStateLeftButton()
{
	return GetAsyncKeyState(VK_LBUTTON);
}

short APIWrapper::GetAsyncKeyStateRightButton()
{
	return GetAsyncKeyState(VK_RBUTTON);
}

int APIWrapper::stricmp(const char* string1, const char* string2) {
	return _stricmp(string1, string2);
}

static bool implCreateDirectory(const char* path, void* security_attributes)
{
	return CreateDirectory(path, (LPSECURITY_ATTRIBUTES)security_attributes);
}

short implGetAsyncKeyState(int key)
{
	return GetAsyncKeyState(key);
}

static char* implPathFindExtension(const char* path) {
	return PathFindExtension(path);
}
