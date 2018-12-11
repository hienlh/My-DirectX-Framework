#pragma once

class CDebug
{
public:
	static void Log(std::string message);
	static void Log(long message);
	static void Log(double message);
	static void Log(const char* szFormat, ...);
	static void Log(const wchar_t* szFormat, ...);
};
