#pragma once
#include "Header.h"
#include "Scene.h"
#include "Window.h"
#include "Input.h"

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
		CGraphic* m_pGraphic = nullptr;
		CInput* m_pInput = nullptr;

		//std::list<CGameObject*> m_gameObjectList{};
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
		void SetCurrentScene(CScene* scene);
		CScene* GetCurrentScene();
		
		// Public methods
	public:
		bool Run();
		//void AddGameObject(CGameObject* pGameObject);

		// Instantiate method
	public:
		static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy();
		static CGameManager* GetInstance();
	};
}
