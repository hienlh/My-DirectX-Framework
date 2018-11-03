#pragma once
#include "GameObject.h"

namespace Framework
{
	class CGraphic final
	{
		// Used for singleton pattern
	private:
		static CGraphic* __instance;
		
		// Cons / Des
	private:
		CGraphic() = default;
		~CGraphic() = default;

		// Properties
	private:
		Direct3D* m_pDirect3D = nullptr;
		Device* m_pDevice = nullptr;
		Surface* m_pBackBuffer = nullptr;
		Sprite* m_pSpriteHandler = nullptr;
		
		// Getter / Setters
	public:
		Direct3D* Get_Direct3D() { return this->m_pDirect3D; }
		Device* Get_Device() { return this->m_pDevice; }
		Surface* Get_BackBuffer() { return this->m_pBackBuffer; }
		Sprite* Get_SpriteHandler() { return m_pSpriteHandler; }

		// Internal methods
	private:
		bool Init(HWND hWind, bool fullscreen);
		void Release();

		// Public methods
	public:
		bool Render(const std::list<CGameObject*> &gameObjectList);
		void Draw(Texture* texture, Vector2 position, Rect* pSourceRect = nullptr);
		
		Texture* CreateTexture(LPCWSTR texturePath, DWORD &textureWidth, DWORD &textureHeight);
			
		// Static methods
	public:
		static void Instantiate(HWND hWnd, bool fullscreen);
		static void Destroy();
		static CGraphic* GetInstance();
	};	
}