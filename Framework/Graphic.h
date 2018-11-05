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
<<<<<<< HEAD
		virtual ~CGraphic() = default;

		// Getters / Setters
	public:
		LPDIRECT3D9 Get_Direct3D() const { return this->m_d3d; }
		LPDIRECT3DDEVICE9 Get_Direct3DDevice() const { return this->m_d3ddev; }
		LPDIRECT3DSURFACE9 Get_BackBuffer() const { return this->m_backbuffer; }
		LPD3DXSPRITE Get_SpriteHandler() const { return m_spriteHandler; }
		Vector2 GetImageSize(LPCSTR imagePath);

		void SetTransform(Matrix &orthographicMatrix, Matrix &identityMatrix, Matrix &viewMatrix);

		// Abstract methods
	public:
		bool Render(std::set<CGameObject*> list_game_objects);
		void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
		void Draw(float x, float y, float width, float height, LPDIRECT3DTEXTURE9 texture);

		LPDIRECT3DTEXTURE9 CreateTexture(LPCSTR texturePath);
		LPDIRECTINPUT8 CreateDirect();
		LPDIRECTINPUTDEVICE8 CreateKeyboard(LPDIRECTINPUT8 dinput);
		LPDIRECTINPUTDEVICE8 CreateMouse(LPDIRECTINPUT8 dinput);

=======
		bool Render(const std::list<CGameObject*> &gameObjectList);
		void Draw(Texture* texture, Vector2 position, Rect* pSourceRect = nullptr);
		
		Texture* CreateTexture(LPCWSTR texturePath, DWORD &textureWidth, DWORD &textureHeight);
			
>>>>>>> origin/dev
		// Static methods
	public:
		static void Instantiate(HWND hWnd, bool fullscreen);
		static void Destroy();
		static CGraphic* GetInstance();
	};	
}