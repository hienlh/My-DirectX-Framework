#pragma once

namespace Framework {

	class CSprite
	{
	private:
		Texture* m_pTexture = nullptr;
		Rect m_sourceRect = { 0,0,0,0 };
		Vector2 m_anchor = { 0.5, 0.5 };

		//cons / des
	private:
		CSprite() = default;
	public:
		CSprite(Texture* texture, Rect sourceRect = {0,0,0,0}, Vector2 anchor = { 0.5 , 0.5 });
		~CSprite();

		//Getter / Setter
	public:
		Texture* GetTexture() const { return m_pTexture; }
		Vector2 GetSize() const { return m_sourceRect.Size(); }
		Rect GetSourceRect() const { return m_sourceRect; }
		Vector2 GetAnchor() const { return m_anchor; }

		/*bool SetTexture(std::string textureName);
		void SetSourceRect(Rect sourceRect) { m_sourceRect = sourceRect; }*/
		void SetAnchor(Vector2 anchor) { m_anchor = anchor; }
	};

}