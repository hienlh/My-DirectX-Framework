#include "stdafx.h"
#include "GameManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Input.h"
#include <string>
#include "Physic.h"
#include "Time.h"

using namespace Framework;

CGameManager* CGameManager::__instance = nullptr;
	
void CGameManager::SetCurrentScene(CScene* scene)
{
	m_currentScene = scene;
}

CScene* CGameManager::GetCurrentScene()
{
	return m_currentScene;
}

bool CGameManager::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	bool result = false;
	do
	{
		CWindow::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
		m_pWindow = CWindow::GetInstance();
		if (!m_pWindow)
			break;
		
		CGraphic::Instantiate(m_pWindow->Get_WindowHandle(), fullscreen);
		m_pGraphic = CGraphic::GetInstance();
		if (!m_pGraphic)
			break;

		CInput::Instantiate();
		m_pInput = CInput::GetInstance();
		if (!m_pInput)
			break;

		result = true;
	} while (false);

	return result;
}

void CGameManager::Release()
{
	CWindow::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
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
		DWORD dt = now - frameStart;
		//DWORD dt = 20;
		CTime::GetInstance()->SetDeltaTime(dt);
		CTime::GetInstance()->SetTime(CTime::GetInstance()->Time() + dt);

		if (dt >= tickPerFrame)
		{
			frameStart = now;

<<<<<<< HEAD
			// process game loop
			bool renderResult = CGraphic::GetInstance()->Render(m_currentScene->GetListGameObject());
			if (!renderResult)
			{
				OutputDebugStringA("[Error] m_pDirect3DCore::Render failed\n");
				break;
			}

			auto input = CInput::GetInstance();
			if (input) {
				input->PollKeyboard();
				input->PollMouse();
			}

			CPhysic::GetInstance()->Update(dt);

			if (m_currentScene)
				m_currentScene->Update(dt);
=======
			m_currentScene->Update(dt);
			m_currentScene->Render();
			/*for (auto lis_game_object : lis_game_objects)
			{
				lis_game_object->Update();
				auto x = lis_game_object->Get_Transform()->m_position.x;
				auto y = lis_game_object->Get_Transform()->m_position.y;
				if (y <= 0 && x <= SCREEN_WIDTH / 2)
					lis_game_object->Get_Transform()->m_position.x += dt / 10;
				else if (y < SCREEN_HEIGHT / 2 && x >= SCREEN_WIDTH / 2)
				{
					lis_game_object->Get_Transform()->m_position.y += dt / 10;
				}
				else if (x > 0 && y >= SCREEN_HEIGHT / 2)
					lis_game_object->Get_Transform()->m_position.x -= dt / 10;
				else
					lis_game_object->Get_Transform()->m_position.y -= dt / 10;
			}
*/
// process game loop
			/*bool renderResult = m_pGraphic->Render(m_gameObjectList);
			if (!renderResult)
				break;*/
>>>>>>> origin/dev
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
