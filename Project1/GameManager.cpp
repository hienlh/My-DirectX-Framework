#include "GameManager.h"
#include "Macros.h"
#include "Window.h"
#include "Direct3DCore.h"
#include "Input.h"
#include <string>

using namespace Framework::GameManager;

// Internal Game Manager Class
class CGameManager_Internal final : public IGameManager
{
private:
	static CGameManager_Internal* __instance;

	// Properties
private:
	Framework::Base::IWindow* m_pWindow = nullptr;
	CScene* m_currentScene = nullptr;

	// Cons/Des
public:
	CGameManager_Internal() = default;
	~CGameManager_Internal() = default;
	
	// Getters / Setters
public:
	Framework::Base::IWindow* GetWindow()
	{
		return m_pWindow;
	}

	// Override methods
public:
	bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
	{
		bool result = false;
		do
		{
			m_pWindow = Framework::Base::IWindow::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
			
			if (!m_pWindow)
			{
				OutputDebugStringA("[Error] IWindow::Instantiate failed\n");
				break;
			}
			HWND hWnd = m_pWindow->Get_WindowHandle();

			// Init Direct3DCore
			Framework::Base::IDirect3DCore::Instantiate(hWnd, fullscreen);

			if (!Framework::Base::IDirect3DCore::GetInstance())
			{
				OutputDebugStringA("[Error] IDirect3DCore::Instantiate failed\n");
				break;
			}

			result = true;
		} while (false);

		return true;
	}

	void Destroy()
	{
		SAFE_DELETE(m_pWindow);
		CScene::Destroy(m_currentScene);
	}

	// Static methods
public:
	static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
	static void Release();
	static CGameManager_Internal* GetInstance();
	void SetCurrentScene(CScene* scene)
	{
		m_currentScene = scene;
	}
	CScene* GetCurrentScene()
	{
		return m_currentScene;
	}
	
	bool Run() override
	{
		DWORD frameStart = GetTickCount();
		DWORD tickPerFrame = 1000 / FRAME_RATE;

		MSG message = {};
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

				auto input = Framework::Base::CInput::GetInstance();
				if (input) {
					input->PollKeyboard();
					input->PollMouse();
				}

				if(m_currentScene)
					m_currentScene->Update(dt);
				// process game loop
				bool renderResult = Framework::Base::IDirect3DCore::GetInstance()->Render(m_currentScene->GetListGameObject());
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
};


CGameManager_Internal* CGameManager_Internal::__instance = nullptr;

void CGameManager_Internal::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		if (!__instance) { __instance = new CGameManager_Internal(); };

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			SAFE_DELETE(__instance);
	}
}

void CGameManager_Internal::Release()
{
	__instance->Destroy();
	SAFE_DELETE(__instance);
}

CGameManager_Internal* CGameManager_Internal::GetInstance()
{
	return __instance;
}

// Game Manager Interface Implementation

void IGameManager::SetCurrentScene(CScene* scene)
{
	CGameManager_Internal::GetInstance()->SetCurrentScene(scene);
}

CScene* IGameManager::GetCurrentScene()
{
	auto scene = CGameManager_Internal::GetInstance()->GetCurrentScene();
	return scene;
}

Framework::Base::IWindow* IGameManager::GetWindow()
{
	const auto result = CGameManager_Internal::GetInstance()->GetWindow();
	return result;
}

void IGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	CGameManager_Internal::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
}

void Framework::GameManager::IGameManager::Release()
{
	CGameManager_Internal::Release();
}

IGameManager * Framework::GameManager::IGameManager::GetInstance()
{
	return CGameManager_Internal::GetInstance();
}
