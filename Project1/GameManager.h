#pragma once
#include "Header.h"
#include "GameObject.h"
#include "Window.h"
#include "Graphic.h"

namespace Framework
{
	namespace GameManager
	{
		// Game Manager Interface
		class IGameManager
		{			
			// Cons / Des
		public:
			IGameManager() = default;
			virtual ~IGameManager() = default;

			// Getters / Setters
		public:
			virtual Base::IWindow* Get_Window() = 0;
			virtual Base::IGraphic* Get_Direct3DCore() = 0;

			// Abstract methods
		public:
			virtual bool Run() = 0;
			virtual void AddGameObject(Object::CGameObject* pGameObject) = 0;

			// Instantiate method
		public:
			static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
			static void Destroy();

			static IGameManager* GetInstance();
		};
	}
}
