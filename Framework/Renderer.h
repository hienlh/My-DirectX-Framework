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
		CSprite *m_pRootSprite = nullptr;
		CSprite *m_pSprite = nullptr;
		DWORD m_alpha = 255, m_fillColor = COLOR_WHITE;
		int m_zOrder = 0;
		bool m_flipX = false, m_flipY = false;

		//Getter / Setter
	public:
		CSprite* GetSprite() const { return m_pSprite; }
		float GetWidth() const { return m_pSprite ? m_pSprite->GetSize().x : 0; }
		float GetHeight() const { return m_pSprite ? m_pSprite->GetSize().y : 0; }
		Vector2 GetSize() const { return m_pSprite ? m_pSprite->GetSize() : Vector2(0, 0); }
		Rect GetSourceRect() const { return m_pSprite ? m_pSprite->GetSourceRect() : Rect(0, 0, 0, 0); }
		DWORD GetAlpha() const { return m_alpha; }
		DWORD GetFillColor() const { return m_fillColor; }
		int GetZOrder() const { return m_zOrder; }
		Vector2 GetAnchor() const { return m_pSprite ? m_pSprite->GetAnchor() : Vector2(0, 0); }
		bool GetFlipX() const { return m_flipX; }
		bool GetFlipY() const { return m_flipY; }

		CRenderer* SetSprite(const std::string& textureName, const DWORD &index = -1);
		CRenderer* SetAlpha(const DWORD &alpha) { m_alpha = alpha > 255 ? 255 : alpha;  return this; }
		CRenderer* SetFillColor(const DWORD &color) { m_fillColor = color;  return this; }
		CRenderer* SetZOrder(const int &zOrder) { m_zOrder = zOrder; return this; }
		CRenderer* SetFlipX(const bool &flipX) { m_flipX = flipX; return this; }
		CRenderer* SetFlipY(const bool &flipY) { m_flipY = flipY; return this; }
		CRenderer* SetAnchor(const Vector2 &anchor) { m_pRootSprite->SetAnchor(anchor); return this; };

		// Cons / Des
	public:
		CRenderer() = default;
		CRenderer(const CRenderer &renderer);
		CRenderer(CGameObject* game_object) : CComponent(game_object) {}
		CRenderer(CGameObject* game_object, std::string texture_path) : CComponent(game_object) { this->Init(texture_path); }
		virtual ~CRenderer() = default;

		// Internal methods
	private:
		bool Init(std::string textureName, DWORD index = 0);
		void Release() const;

	public:
		void Update(DWORD dt) override;
		void Render() override;
		CRenderer* Clone() override { return new CRenderer(*this); }

		// Static methods
	public:
		static void Destroy(CRenderer* &instance);
		// Friend
	};
}