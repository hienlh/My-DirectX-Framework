#include "GameManager.h"
#include "Macros.h"
#include "Window.h"
#include "Graphic.h"
#include "Input.h"
#include <string>

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
	SAFE_DELETE(m_pWindow);
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
		if (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
		{
			// check for escape key (to exit program)
			if (message.message == WM_QUIT)
				done = true;

			// translate message and send back to WinProc
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			auto input = CInput::GetInstance();
			if (input) {
				input->PollKeyboard();
				input->PollMouse();
			}

			if (m_currentScene)
				m_currentScene->Update(dt);
			// process game loop
			bool renderResult = CGraphic::GetInstance()->Render(m_currentScene->GetListGameObject());
			if (!renderResult)
			{
				OutputDebugStringA("[Error] m_pDirect3DCore::Render failed\n");
				break;
			}
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return true;
}

void CGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		if (!__instance)
			SAFE_ALLOC(__instance, CGameManager)

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			SAFE_DELETE(__instance);
	}
}

void CGameManager::Destroy()
{
	if(__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CGameManager * CGameManager::GetInstance()
{
	return __instance;
}
