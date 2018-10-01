#include "GameManager.h"
#include "Macros.h"
#include "Window.h"
#include "Direct3DCore.h"

using namespace Framework::GameManager;

// Internal Game Manager Class
class CGameManager_Internal final : public IGameManager
{
private:
	static CGameManager_Internal* __instance;

	static std::vector<Framework::Object::CGameObject*> lis_game_objects;

	// Properties
private:
	Framework::Base::IWindow* m_pWindow = nullptr;
	Framework::Base::IDirect3DCore* m_pDirect3DCore = nullptr;

	// Cons/Des
public:
	CGameManager_Internal() = default;
	~CGameManager_Internal() = default;
	
	// Getters / Setters
public:

	// Override methods
public:
	bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
	{
		bool result = false;
		do
		{
			// Init Window
			Framework::Base::IWindow::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
			m_pWindow = Framework::Base::IWindow::GetInstance();
			
			if (!m_pWindow)
			{
				OutputDebugStringA("[Error] IWindow::Instantiate failed\n");
				break;
			}
			HWND hWnd = m_pWindow->Get_WindowHandle();

			// Init Direct3DCore
			Framework::Base::IDirect3DCore::Instantiate(hWnd, fullscreen);
			m_pDirect3DCore = Framework::Base::IDirect3DCore::GetInstance();

			if (!m_pDirect3DCore)
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
		Framework::Base::IWindow::Release();
		Framework::Base::IDirect3DCore::Release();
	}
	static void AddGameObject(Framework::Object::CGameObject*);

	// Static methods
public:
	static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
	static void Release();
	static CGameManager_Internal* GetInstance();
	
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

				for (auto lis_game_object : lis_game_objects)
				{
					lis_game_object->Update();
					auto x = lis_game_object->GetTranform()->position.x;
					auto y = lis_game_object->GetTranform()->position.y;
					if (y <= 0 && x <= SCREEN_WIDTH / 2)
						lis_game_object->GetTranform()->position.x += dt / 10;
					else if (y < SCREEN_HEIGHT / 2 && x >= SCREEN_WIDTH / 2)
					{
						lis_game_object->GetTranform()->position.y += dt / 10;
					}
					else if (x > 0 && y >= SCREEN_HEIGHT / 2)
						lis_game_object->GetTranform()->position.x -= dt / 10;
					else
						lis_game_object->GetTranform()->position.y -= dt / 10;
				}

				// process game loop
				bool renderResult = m_pDirect3DCore->Render(lis_game_objects);
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

std::vector<Framework::Object::CGameObject*> CGameManager_Internal::lis_game_objects;

CGameManager_Internal * CGameManager_Internal::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGameManager_Internal);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			SAFE_DELETE(__instance);
	}
}

void CGameManager_Internal::Release()
{
	SAFE_DELETE(__instance);
}

void CGameManager_Internal::AddGameObject(Framework::Object::CGameObject* game_object)
{
	lis_game_objects.push_back(game_object);
}

IGameManager* IGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	return __instance;
}

// Game Manager Interface Implementation

void IGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	return CGameManager_Internal::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
}

void Framework::GameManager::IGameManager::Release()
{
	CGameManager_Internal::Destroy();
}

void Framework::GameManager::IGameManager::AddGameObject(Object::CGameObject* game_object)
{
	CGameManager_Internal::AddGameObject(game_object);
}
