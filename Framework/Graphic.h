#pragma once
#include "Header.h"
#include "GameObject.h"

namespace Framework
{
	// Direct3D Core Interface
	class CGraphic final
	{
	private:
		static CGraphic* __instance;

		// Properties
	private:
		LPDIRECT3D9 m_d3d = nullptr;
		LPDIRECT3DSURFACE9 m_backbuffer = nullptr;
		LPD3DXSPRITE m_spriteHandler = nullptr;

	public:
		LPDIRECT3DDEVICE9 m_d3ddev = nullptr;

		//Private method
	private:
		bool Init(HWND hWind, bool fullscreen);
		void Release();

		// Cons / Des
	private:
		CGraphic() = default;
	public:
		bool Render(const std::list<CGameObject*> &gameObjectList);
		void Draw(Texture* texture, Vector2 position, Rect* pSourceRect = nullptr);
		
		Texture* CreateTexture(LPCWSTR texturePath, DWORD &textureWidth, DWORD &textureHeight);
			
		// Static methods
	public:
		static void Instantiate(HWND HWnd, bool fullscreen);
		static void Destroy();

		static CGraphic* GetInstance();
	};
}