#include "stdafx.h"

#include "GameManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Physic.h"
#include "Time.h"

using namespace Framework;

CGameManager* CGameManager::__instance = nullptr;

bool CGameManager::Init(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth,
	const int& screenHeight, const bool& fullscreen)
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
	NotifyStart(); //Notify to observer when game start

	m_isRunning = true;

	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;

	m_currentScene->LoadQuadTree();

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
		DWORD dt = now - frameStart;
		dt = 20; // For Debug

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			// process game loop

			CPhysic::GetInstance()->Update(dt);

			//CDebug::Log("Physic time: %d \n", GetTickCount() - frameStart);

			if (m_currentScene)
				m_currentScene->Update(dt);

			//CDebug::Log("Update time: %d \n", GetTickCount() - frameStart);

			m_currentScene->Render();
			//CDebug::Log("Render time: %d \n", GetTickCount() - frameStart);
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


void CGameManager::Instantiate(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth,
	const int& screenHeight, const bool& fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGameManager);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
		{
			__instance->Release();
			SAFE_DELETE(__instance);
		}
	}
}

void CGameManager::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CGameManager* CGameManager::GetInstance()
{
	return __instance;
}
