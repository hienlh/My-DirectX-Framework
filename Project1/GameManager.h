#pragma once
#include "Header.h"
#include "GameObject.h"
#include "Scene.h"
#include "Direct3DCore.h"
#include "Window.h"

namespace Framework
{
	namespace GameManager
	{
		// Game Manager Interface
		class IGameManager
		{
		protected:
			IGameManager() = default;
	
			// Getters / Setters
		public:
			void SetCurrentScene(CScene* scene);
			CScene* GetCurrentScene();

			// Abstract methods
		public:
			virtual bool Run() = 0;

			// Instantiate method
		public:
			~IGameManager() = default;
			static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
			static void Release();
			static IGameManager* GetInstance();
		};
	}
}
