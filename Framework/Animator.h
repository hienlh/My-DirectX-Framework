#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Animation.h"

namespace Framework
{

	class CTransition
	{
	private:
		CWString m_dstAnimationName = L"";
		std::map<CWString, bool> m_conditions = {};
		bool m_hasExitTime = false;
		bool m_isRelatedTo = false;

	public:
		CTransition(CWString name) { m_dstAnimationName = name; }

	public:
		CTransition* SetCondition(CWString conditionName, bool value) { m_conditions[conditionName] = value; return this; }
		CTransition* SetHasExitTime(bool hasExitTime) { m_hasExitTime = hasExitTime; return this; };
		CTransition* SetRelatedTo(bool relatedTo) { m_isRelatedTo = relatedTo; return this; }

		std::map<CWString, bool>& GetConditions() { return m_conditions; }
		CWString GetDestinationAnimationName() const { return m_dstAnimationName; }
		bool GetHasExitTime() const { return m_hasExitTime; }
		bool GetRelatedTo() const { return m_isRelatedTo; }
	};

	class CAnimator final : public CComponent
	{
		// Properties
	private:
		std::map<CWString, CAnimation*> m_Animations = {};
		std::map<CWString, std::list<CTransition*> > m_transitions = {};
		std::map<CWString, bool> m_boolConditions = {};
		CAnimation* m_pCurrentAnimation = nullptr;
		CAnimation* m_pRootAnimation = nullptr;

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
		CAnimator* AddAnimation(CWString animationName);
		CAnimator* AddTransition(CWString srcAnimationName, CWString dstAnimationName, bool hasExitTime = false,
		                         CWString conditionName = L"", bool value = false, bool relatedTo = false);
		CAnimator* SetRootAnimation(CWString animationName);

		CAnimation *GetCurrentAnimation() const;
		CSprite *GetCurrentSprite() const;
		CTransition *GetTransition(CWString srcAnimationName, CWString dstAnimationName);

		CAnimator* AddBool(CWString name, bool value);
		CAnimator* SetBool(CWString name, bool value);
		bool GetBool(CWString name);

	public:
		void Update(DWORD dt) override;
		void Render() override;

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);

	};
}
