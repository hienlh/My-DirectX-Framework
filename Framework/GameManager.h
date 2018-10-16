#pragma once
#include "Header.h"
#include "Scene.h"
#include "Window.h"

namespace Framework
{
	// Game Manager Interface
	class CGameManager
	{
	private:
		static CGameManager* __instance;

		// Properties
	private:
		CWindow* m_pWindow = nullptr;
		CScene* m_currentScene = nullptr;

		// Cons/Des
	private:
		CGameManager() = default;
	public:
		virtual ~CGameManager() = default;

		//Private Method
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		void Release();

		// Getters / Setters
	public:
		void SetCurrentScene(CScene* scene) { m_currentScene = scene; }
		CScene* GetCurrentScene() const { return m_currentScene; }
		CWindow* GetWindow() const { return m_pWindow; }

		// Abstract methods
	public:
		bool Run();

		// Instantiate method
	public:
		static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy();
		static CGameManager* GetInstance();
	};
}
