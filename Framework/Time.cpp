#include "Time.h"
#include "Macros.h"

using namespace Framework;

CTime* CTime::__instance = nullptr;

CTime::CTime()
{
	m_deltaTime = 0;
	m_time = 0;
}

void CTime::Release()
{
	
}

CTime* CTime::GetInstance()
{
	if(!__instance)
	{
		SAFE_ALLOC(__instance, CTime);
	}

	return __instance;
}

void CTime::Destroy()
{
	__instance->Release();
	SAFE_DELETE(__instance);
}
