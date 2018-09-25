#pragma once
#include "Header.h"

namespace Framework
{
	namespace GameManager
	{
		// Game Manager Interface
		class IGameManager
		{
		protected:
			static IGameManager* __instance;

		public:
			IGameManager() {};
			virtual ~IGameManager() {};

		public:
			static IGameManager* GetInstance();

			virtual bool Init(HINSTANCE hInstance, int nShowCmd,
			                  int screenWidth, int screenHeight,
			                  bool fullscreen) = 0;
			virtual void Destroy() = 0;
			virtual bool Run() = 0;
		};
	}
}
