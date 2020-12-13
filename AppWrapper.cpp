
#include "AppWrapper.h"
#include "App.h"

LPCSTR AppWrapper::GetErrorString(INT nID)
{
	return CApp::GetErrorString(nID);
}

LPCSTR AppWrapper::GetModulePath()
{
	return CApp::GetModulePath();
}
