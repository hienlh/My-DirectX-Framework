#include "GameManager.h"
#include "Direct3DCore.h"

using namespace Framework::GameManager;

// Internal Game Manager Class
class CGameManager_Internal final : public IGameManager
{
	// Properties
private:
	Framework::Direct3DCore::IDirect3DCore* m_pDirect3DCore;
	MSG m_message;

	// Cons/Des
public:
	CGameManager_Internal()
	{
		m_pDirect3DCore = nullptr;
		m_message = {};
	}

	~CGameManager_Internal()
	{
		m_pDirect3DCore->Destroy();
	}

	// Getters
public:
	MSG Get_Message() { return m_message; }

	// Override methods
public:
	bool Init(HINSTANCE hInstance, int nShowCmd,
	          int screenWidth, int screenHeight,
	          bool fullscreen) override
	{
		bool result = false;
		do
		{
			// Init Direct3DCore
			m_pDirect3DCore = Framework::Direct3DCore::IDirect3DCore::GetInstance();
			if (m_pDirect3DCore->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			{
				OutputDebugStringA("[Error] m_pDirect3DCore::Init failed\n");
				break;
			}
	
			result = true;
		} while (false);

		return true;
	}

	void Destroy() override
	{
	}

	bool Run() override
	{
		DWORD frameStart = GetTickCount();
		DWORD tickPerFrame = 1000 / FRAME_RATE;

		bool done = false;
		while (!done)
		{
			if (PeekMessageA(&m_message, nullptr, 0, 0, PM_REMOVE))
			{
				// check for escape key (to exit program)
				if (m_message.message == WM_QUIT)
					done = true;

				// translate message and send back to WinProc
				TranslateMessage(&m_message);
				DispatchMessageA(&m_message);
			}

			DWORD now = GetTickCount();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			if (dt >= tickPerFrame)
			{
				frameStart = now;

				// process game loop
				bool renderResult = m_pDirect3DCore->Render();
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

	// Internal methods
private:
};

// Game Manager Initialization
IGameManager* IGameManager::__instance = nullptr;

IGameManager* IGameManager::GetInstance()
{
	SAFE_ALLOC(__instance, CGameManager_Internal);
	return __instance;
}
