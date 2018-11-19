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

		//Getter / Setter
	public:
		Texture* GetTexture() const { return m_pTexture; }
		float GetWidth() const { return m_textureWidth; }
		float GetHeight() const { return m_textureHeight; }
		Vector2 GetSize() const { return Vector2(m_textureWidth, m_textureHeight); }

		void SetTexture(LPCWSTR texture_name);
		//void SetTexture(CTexture texture) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		void SetWidth(float width) { m_textureWidth = width; }
		void SetHeight(float height) { m_textureHeight = height; }

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