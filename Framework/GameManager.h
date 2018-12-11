#pragma once
#include "GameObject.h"
#include "Window.h"
#include "Graphic.h"
#include "Scene.h"
#include "Input.h"

namespace Framework
{
	// Game Manager Interface
	class CGameManager final
	{
		// Used for singleton pattern
	private:
		static CGameManager* __instance;

		// Cons / Des
	private:
		CGameManager() = default;
		~CGameManager() = default;

		// Properties
	private:
		CWindow* m_pWindow = nullptr;
		CScene* m_currentScene = nullptr;

		// Internal methods
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		void Release();

		// Getters / Setters
	public:
		void SetCurrentScene(CScene* scene) { m_currentScene = scene; }
		CScene* GetCurrentScene() const { return m_currentScene; }
		CWindow* GetWindow() const { return m_pWindow; }
		
		// Public methods
	public:
		bool Run();

		// Instantiate method
	public:
		static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy();
		static CGameManager* GetInstance();
	};
}