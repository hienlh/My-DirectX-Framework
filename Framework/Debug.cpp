#include "stdafx.h"
#include "Debug.h"

#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>

void CDebug::Log(std::string message)
{
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugStringW(sw);
}

void CDebug::Log(long message)
{
	OutputDebugStringA(std::to_string(message).c_str());
}

void CDebug::Log(double message)
{
	OutputDebugStringA(std::to_string(message).c_str());
}

void CDebug::Log(const char* szFormat, ...)
{
	char szBuff[4096];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugStringA(szBuff);
}

void CDebug::Log(const wchar_t* szFormat, ...)
{
	va_list arg;
	va_start(arg, szFormat);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, szFormat, arg);
	va_end(arg);
	OutputDebugString(dbg_out);
}
