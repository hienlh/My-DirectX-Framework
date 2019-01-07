#include "stdafx.h"
#include "Audio.h"
#include "GameManager.h"

using namespace Framework;

CAudio* CAudio::__instance = nullptr;

bool CAudio::Init()
{
	const HWND hWnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	bool result = false;

	do
	{
		// Create DirectSound manager object 
		SAFE_ALLOC(m_soundManager, CSoundManager);

		// Initialize DirectSound 
		if (m_soundManager->Initialize(hWnd, DSSCL_PRIORITY) != DS_OK)
			break;

		// Set the primary buffer format 
		if (m_soundManager->SetPrimaryBufferFormat(2, 22050, 16) != DS_OK)
			break;

		result = true;
	} while (false);

	return result;
}

void CAudio::Release()
{
	SAFE_DELETE(m_soundManager);
}

void CAudio::Instantiate()
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CAudio);
		if (!__instance->Init())
		{
			__instance->Release();
			SAFE_DELETE(__instance);
		}
	}
}

void CAudio::Destroy()
{
	__instance->Release();
	SAFE_DELETE(__instance);
}

CSound* CAudio::Load(CString fileName) const
{
	CSound* pSound = nullptr;
	// Convert (const char*) to (wchar_t*)
	std::wstring wFileName(fileName, fileName + strlen(fileName));

	// Attempt to load the wave file
	if (m_soundManager->Create(&pSound, (LPWSTR)wFileName.c_str()) != DS_OK)
		pSound = nullptr;

	return pSound;
}

void CAudio::Play(CSound* pSound)
{
	if (pSound)
		pSound->Play();
}

void CAudio::PlayLoop(CSound* pSound)
{
	if (pSound)
		pSound->Play(0, DSBPLAY_LOOPING);
}

void CAudio::Stop(CSound* pSound)
{
	if (pSound)
		pSound->Stop();
}

CAudio* CAudio::GetInstance()
{
	if (!__instance)
		Instantiate();

	return __instance;
}