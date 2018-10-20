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

		DWORD m_animationCountWidth = 0, m_animationCountHeight = 0;
		DWORD m_animationWidth = 0, m_animationHeight = 0;
		DWORD m_currentAnimation = 0, m_countAnimation = 0;
		DWORD m_currentDelay = 0, m_thresholdDelay = 0;

		Texture* m_pTexture = nullptr;

		// Cons / Des
	private:
		CAnimator() = default;
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init(LPCWSTR texturePath, DWORD countWidth, DWORD countHeight, DWORD count, DWORD delay);
		void Release();

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CAnimator* Instantiate(UObjectData data);
		static void Destroy(CAnimator* &instance);

	};
}
