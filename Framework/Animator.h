#pragma once
#include "stdafx.h"
#include "Component.h"
#include "CTexture.h"
#include "Animation.h"

namespace Framework
{
	class CAnimator final : public CComponent
	{
		// Properties
	private:
		std::map<LPCWSTR, CAnimation*> m_Animations = {};
		CAnimation* m_pCurrentAnimation;

		// Cons / Des
	public:
		CAnimator() = default;
		CAnimator(CGameObject* game_object) : CComponent(game_object) {}
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init();
		void Release();

		//Getter / Setter
	public:
		void AddAnimation(LPCWSTR animationName);
		void SetCurrentAnimation(LPCWSTR animationName);

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);

	};
}
