#pragma once
#include "GameObject.h"
#include "Window.h"
#include "Scene.h"
#include "GameSubject.h"

namespace Framework
{
	// Game Manager Interface
	class CGameManager final : public CGameSubject
	{
		// Used for singleton pattern
	private:
		static CGameManager* __instance;

		// Cons / Des
	private:
		CGameManager() = default;
		CGameManager(const CGameManager& game_manager) : CGameSubject(game_manager){}
		~CGameManager() = default;

		// Properties
	private:
		CWindow* m_pWindow = nullptr;
		CScene* m_currentScene = nullptr;
		bool m_isRunning = false;
		bool m_isDebugging = false;

		// Internal methods
	private:
		bool Init(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth, const int& screenHeight,
		          const bool& fullscreen);
		void Release();

		// Getters / Setters
	public:
		CGameManager* SetCurrentScene(CScene* scene) { m_currentScene = scene; return this; }
		CGameManager* SetIsDebugging(const bool &isDebugging) { m_isDebugging = isDebugging; return this; }

		CScene* GetCurrentScene() const { return m_currentScene; }
		CWindow* GetWindow() const { return m_pWindow; }
		const bool &GetIsDebugging() const { return m_isDebugging; }

		const bool &IsRunning() const { return m_isRunning; }
		
		// Public methods
	public:
		bool Run();

		// Instantiate method
	public:
		static void Instantiate(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth,
		                        const int& screenHeight, const bool& fullscreen);
		static void Destroy();
		static CGameManager* GetInstance();
	};
}
