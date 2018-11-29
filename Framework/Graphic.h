#pragma once
#include "GameObject.h"

class CTexture;

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
		ID3DXSprite* m_pSpriteHandler = nullptr;
		IDirect3DVertexBuffer9* m_pVertexBuffer = nullptr;
		
		// Getter / Setters
	public:
		Direct3D* Get_Direct3D() const { return this->m_pDirect3D; }
		Device* Get_Device() const { return this->m_pDevice; }
		Surface* Get_BackBuffer() const { return this->m_pBackBuffer; }
		ID3DXSprite* Get_SpriteHandler() const { return m_pSpriteHandler; }

		void SetTransform(Matrix &orthographicMatrix, Matrix &identityMatrix, Matrix &viewMatrix);

		// Internal methods
	private:
		bool Init(HWND hWind, bool fullscreen);
		void Init_VertexGraphic(std::vector<CUSTOMVERTEX> vertices);
		void Release();

		// Public methods
	public:
		bool Render(std::set<CGameObject*> list_game_objects);
		void Draw(Texture* texture, Vector3* position = nullptr, Rect* pSourceRect = nullptr, Vector2* center = nullptr,
		          float angle = 0, DWORD fillColor = COLOR_WHITE, Vector3 *scale = nullptr, bool flipX = false, bool flipY = false) const;
		void Draw(CSprite* sprite, Vector3* position = nullptr, float angle = 0, Vector3 *scale = nullptr, 
				  bool flipX = false, bool flipY = false) const;
		void DrawRectangle(Rect rect, DWORD color = NULL);
		
		Texture* CreateTexture(LPCWSTR texturePath, D3DCOLOR transparentColor = COLOR_BLACK);
			
		// Static methods
	public:
		static void Instantiate(HWND hWnd, bool fullscreen);
		static void Destroy();
		static CGraphic* GetInstance();
	};	
}
