#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Component.h"

namespace Framework {
	class CGameObject;
}

namespace Framework
{
	class CGameObject;

	class CRenderer final : public CComponent
	{
		// Properties
	private:
		Texture* m_pTexture = nullptr;
		DWORD m_textureWidth = -1, m_textureHeight = -1;
		DWORD m_renderPosX = 0, m_renderPosY;
		DWORD m_alpha = 255;
		int m_zOrder = 0;
		bool m_flipX = false, m_flipY = false;

		//Getter / Setter
	public:
		Texture* GetTexture() const { return m_pTexture; }
		float GetWidth() const { return m_textureWidth; }
		float GetHeight() const { return m_textureHeight; }
		Vector2 GetSize() const { return Vector2(m_textureWidth, m_textureHeight); }
		DWORD GetAlpha() const { return m_alpha; }
		int GetZOrder() const { return m_zOrder; }
		bool GetFlipX() const { return m_flipX; }
		bool GetFlipY() const { return m_flipY; }

		CRenderer* SetTexture(CWString texture_name);
		CRenderer* SetTexture(Texture* texture) { m_pTexture = texture; return this; };
		//void SetTexture(CTexture texture) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		CRenderer* SetWidth(float width) { m_textureWidth = width; return this; }
		CRenderer* SetHeight(float height) { m_textureHeight = height; return this; }
		CRenderer* SetAlpha(DWORD alpha) { m_alpha = alpha > 255 ? 255 : alpha;  return this; }
		CRenderer* SetZOrder(int zOrder) { m_zOrder = zOrder; return this; }
		CRenderer* SetFlipX(bool flipX) { m_flipX = flipX; return this; }
		CRenderer* SetFlipY(bool flipY) { m_flipY = flipY; return this; }
		CRenderer* SetRenderPosX(DWORD posX) { m_renderPosX = posX; return this; }
		CRenderer* SetRenderPosY(DWORD posY) { m_renderPosY = posY; return this; }

		// Cons / Des
	public:
		CRenderer() = default;
		CRenderer(CGameObject* game_object) : CComponent(game_object) {}
		//CRenderer(Object::CGameObject* game_object, CTexture texture) : CComponent(game_object) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		CRenderer(CGameObject* game_object, LPCWSTR texture_path) : CComponent(game_object) { this->Init(texture_path); }
		virtual ~CRenderer() = default;

		// Internal methods
	private:
		bool Init(LPCWSTR textureName);
		void Release();

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CRenderer* Instantiate();
		static void Destroy(CRenderer* &instance);

		// Override method
	public:

	};
}