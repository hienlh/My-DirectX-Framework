#pragma once
#include "Header.h"

namespace Framework
{
	namespace Base
	{
		// Direct3D Core Interface
		class IDirect3DCore
		{		
			// Cons / Des
		public:
			IDirect3DCore() = default;
			~IDirect3DCore() = default;

			// Getter / Setters
		public:
			virtual LPDIRECT3D9 Get_Direct3D() = 0;
			virtual LPDIRECT3DDEVICE9 Get_Direct3DDevice() = 0;
			virtual LPDIRECT3DSURFACE9 Get_BackBuffer() = 0;
			virtual LPD3DXSPRITE Get_SpriteHandler() = 0;

			// Abstract methods
		public:
			virtual bool Render() = 0;
			virtual void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) = 0;

			// Pattern
		public:
			static IDirect3DCore* Instantiate(HWND HWnd, bool fullscreen);
			static void Release();
		};
	}
}
