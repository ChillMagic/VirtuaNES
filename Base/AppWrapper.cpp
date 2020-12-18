
#include "Base/AppWrapper.h"
#include "App/App.h"

LPCSTR AppWrapper::GetErrorString(INT nID)
{
	return CApp::GetErrorString(nID);
}

LPCSTR AppWrapper::GetModulePath()
{
	return CApp::GetModulePath();
}
