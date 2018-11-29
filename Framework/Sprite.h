#pragma once

namespace Framework {

	class CSprite
	{
	private:
		Texture* m_pTexture = nullptr;
		Rect m_sourceRect = { 0,0,0,0 };
		Vector2 m_anchor{};

		//cons / des
	private:
		CSprite() = default;
	public:
		CSprite(CWString name, CWString textureName, Rect *sourceRect = nullptr, Vector2 anchor = VECTOR2_ZERO);
		~CSprite();

		//Getter / Setter
	public:
		Texture* GetTexture() const { return m_pTexture; }
		Vector2 GetSize() const { return m_sourceRect.Size(); }
		Rect GetSourceRect() const { return m_sourceRect; }
		Vector2 GetAnchor() const { return m_anchor; }

		bool SetTexture(CWString textureName);
		void SetSourceRect(Rect sourceRect) { m_sourceRect = sourceRect; }
		void SetAnchor(Vector2 anchor) { m_anchor = anchor; }
	};

}