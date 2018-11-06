#pragma once
#include "stdafx.h"
#include "Component.h"

namespace Framework
{
	class CAnimator final : public CComponent
	{
		// Properties
	private:
		DWORD m_textureWidth = 0, m_textureHeight = 0;

		DWORD m_animationCountWidth = 1, m_animationCountHeight = 1;
		DWORD m_animationWidth = 0, m_animationHeight = 0;
		DWORD m_currentAnimation = 0, m_countAnimation = 0;
		DWORD m_currentDelay = 0, m_thresholdDelay = 0;

		Texture* m_pTexture = nullptr;

		// Cons / Des
	public:
		CAnimator() = default;
		CAnimator(CGameObject* game_object) : CComponent(game_object) {}
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init(LPCWSTR texturePath, DWORD countWidth, DWORD countHeight, DWORD count, DWORD delay);
		void Release();

		//Getter / Setter
	public:
		bool Set(LPCWSTR texturePath = L"", DWORD countWidth = 1, DWORD countHeight = 1, DWORD count = 0, DWORD delay = 0);

		DWORD GetAnimationWidth() const { return m_animationWidth; }
		DWORD GetAnimationHeight() const { return m_animationHeight; }

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);

	};
}
