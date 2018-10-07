#include "GameManager.h"
#include "Macros.h"
#include "Window.h"
#include "Graphic.h"

using namespace Framework::GameManager;

// Internal Game Manager Class
class CGameManager_Internal final : public IGameManager
{
private:
	static CGameManager_Internal* __instance;

	// Properties
private:
	std::vector<Framework::Object::CGameObject*> m_gameObjects;

	Framework::Base::IWindow* m_pWindow = nullptr;
	Framework::Base::IGraphic* m_pDirect3DCore = nullptr;

	// Getters / Setters
public:
	virtual Framework::Base::IWindow* Get_Window() override { return m_pWindow; };
	virtual Framework::Base::IGraphic* Get_Direct3DCore() override { return m_pDirect3DCore; };

	// Cons/Des
public:
	CGameManager_Internal() = default;
	virtual ~CGameManager_Internal() = default;
	
private:
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
			Framework::Base::IGraphic::Instantiate(hWnd, fullscreen);
			m_pDirect3DCore = Framework::Base::IGraphic::GetInstance();

			if (!m_pDirect3DCore)
			{
				OutputDebugStringA("[Error] IDirect3DCore::Instantiate failed\n");
				break;
			}

			result = true;
		} while (false);

		return result;
	}

	void Release()
	{
		Framework::Base::IWindow::Destroy();
		Framework::Base::IGraphic::Destroy();
	}

	// Override methods
private:
	void AddGameObject(Framework::Object::CGameObject* pGameObject) override
	{
		m_gameObjects.push_back(pGameObject);
	}

	bool Run() override
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
				bool renderResult = m_pDirect3DCore->Render(m_gameObjects);
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

	// Static methods
public:
	static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
	static void Destroy();
	static CGameManager_Internal* GetInstance();
};

CGameManager_Internal* CGameManager_Internal::__instance = nullptr;

void CGameManager_Internal::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGameManager_Internal);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			SAFE_DELETE(__instance);
	}
}

void CGameManager_Internal::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CGameManager_Internal* CGameManager_Internal::GetInstance()
{
	return __instance;
}

// Game Manager Interface Implementation

void IGameManager::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	CGameManager_Internal::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
}

void Framework::GameManager::IGameManager::Destroy()
{
	CGameManager_Internal::Destroy();
}

IGameManager * Framework::GameManager::IGameManager::GetInstance()
{
	return CGameManager_Internal::GetInstance();
}
