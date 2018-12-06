#include "stdafx.h"

#include "GameManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Physic.h"

using namespace Framework;

CGameManager* CGameManager::__instance = nullptr;

bool CGameManager::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	bool result = false;
	do
	{
		m_pWindow = CWindow::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);

		if (!m_pWindow)
		{
			OutputDebugStringA("[Error] CWindow::Instantiate failed\n");
			break;
		}
		HWND hWnd = m_pWindow->Get_WindowHandle();

		// Init Direct3DCore
		CGraphic::Instantiate(hWnd, fullscreen);

		if (!CGraphic::GetInstance())
		{
			OutputDebugStringA("[Error] CGraphic::Instantiate failed\n");
			break;
		}

		result = true;
	} while (false);

	return result;
}

void CGameManager::Release()
{
	CWindow::Destroy(m_pWindow);
	CScene::Destroy(m_currentScene);
}

bool CGameManager::Run()
{
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;

	bool done = false;
	while (!done)
	{
		MSG message = {};
		if (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
		{
			// check for escape key (to exit program)
			if (message.message == WM_QUIT)
				done = true;

			// translate message and send back to WinProc
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD now = GetTickCount();
		//DWORD dt = now - frameStart;
		DWORD dt = 20; // For Debug

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			// process game loop

			m_currentScene->Render();

			if (m_currentScene)
				m_currentScene->Update(dt);

			CPhysic::GetInstance()->Update(dt);
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return true;

}

//void CGameManager::AddGameObject(CGameObject* pGameObject)
//{
//	m_gameObjectList.push_back(pGameObject);
//}

void CGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGameManager);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
		{
			__instance->Release();
			SAFE_FREE(__instance);
		}
	}
}

void CGameManager::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_FREE(__instance);
	}
}

CGameManager* CGameManager::GetInstance()
{
	return __instance;
}
