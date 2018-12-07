#pragma once
#include "stdafx.h"
#include "Component.h"
#include "CTexture.h"
#include "Animation.h"

namespace Framework
{
	class CState : public CObject
	{
	public:
		CState(CAnimation *animation);

	private:
		CAnimation* m_animation = nullptr;

	public:
		void Update(DWORD dt) {}
		void Render() {}

		CAnimation* GetAnimation() { return m_animation; }
	};

	class CAnimator final : public CComponent
	{
		// Properties
	private:
		std::unordered_map<LPCWSTR, CAnimation*> m_Animations = {};
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

		CAnimation *GetCurrentAnimation() const;
		CSprite *GetCurrentSprite() const;

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);

	};
}
