#pragma once
#include "Header.h"

namespace Framework
{
	namespace Direct3DCore
	{
		// Direct3D Core Interface
		class IDirect3DCore
		{
		protected:
			static IDirect3DCore* __instance;
		
		public:
			IDirect3DCore() {};
			virtual ~IDirect3DCore() {};

		public:
			static IDirect3DCore* GetInstance();

			virtual bool Init(HINSTANCE hInstance, int nShowCmd,
			                         int screenWidth, int screenHeight,
			                         bool fullscreen) = 0;

			virtual void Destroy() = 0;
			virtual bool Render() = 0;
		};
	}
}
