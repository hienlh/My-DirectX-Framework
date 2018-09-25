#pragma once
#include "Header.h"

namespace Framework
{
	namespace Direct3DCore
	{
		// Direct3D Core Interface
		class Direct3DCore
		{
			friend class Direct3DCore_Internal;
		protected:
			static Direct3DCore* __instance;
		
		protected:
			Direct3DCore() {};
			virtual ~Direct3DCore();

		public:
			static Direct3DCore* GetInstance();

			virtual bool Instantiate(HINSTANCE hInstance, int nShowCmd,
			                         int screenWidth, int screenHeight,
			                         bool fullscreen) = 0;

			virtual bool Destroy() = 0;
		};
	}
}
