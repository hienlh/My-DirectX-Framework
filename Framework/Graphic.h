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
		bool Render(std::vector<CGameObject*> list_game_objects);
		void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
		void Draw(float x, float y, float width, float height, LPDIRECT3DTEXTURE9 texture);

		LPDIRECT3DTEXTURE9 CreateTexture(LPCSTR texturePath);
		LPDIRECTINPUT8 CreateDirect();
		LPDIRECTINPUTDEVICE8 CreateKeyboard(LPDIRECTINPUT8 dinput);
		LPDIRECTINPUTDEVICE8 CreateMouse(LPDIRECTINPUT8 dinput);

		// Static methods
	public:
		static void Instantiate(HWND HWnd, bool fullscreen);
		static void Destroy();

		static CGraphic* GetInstance();
	};
}