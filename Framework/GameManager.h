#pragma once
#include "GameObject.h"
#include "Window.h"
#include "Graphic.h"
#include "Scene.h"

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
		CGraphic* m_pGraphic = nullptr;

		std::list<CGameObject*> m_gameObjectList{};
		CScene* m_currentScene = nullptr;

		// Internal methods
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		void Release();

		
		// Getters / Setters
	public:
		void SetCurrentScene(CScene* scene);
		CScene* GetCurrentScene();
		
		// Public methods
	public:
		bool Run();
		void AddGameObject(CGameObject* pGameObject);

		// Instantiate method
	public:
		static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy();
		static CGameManager* GetInstance();
	};
}