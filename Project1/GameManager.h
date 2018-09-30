#pragma once
#include "Header.h"

namespace Framework
{
	namespace GameManager
	{
		// Game Manager Interface
		class IGameManager
		{
			// Getters / Setters
		public:
			
			// Abstract methods
		public:
			virtual bool Run() = 0;
			
			// Instantiate method
		public:
			static IGameManager* Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
			static void Destroy();
		};
	}
}
