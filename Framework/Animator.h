#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Animation.h"

namespace Framework
{

	class CTransition : public CObject
	{
	private:
		std::string m_dstAnimationName = "";
		std::map<std::string, bool> m_conditions = {};
		bool m_hasExitTime = false;
		bool m_isRelatedTo = false;

	public:
		CTransition(std::string name) { m_dstAnimationName = name; }
		CTransition(const CTransition& transition);
		~CTransition() override = default;

	public:
		CTransition* SetCondition(std::string conditionName, bool value) { m_conditions[conditionName] = value; return this; }
		CTransition* SetHasExitTime(bool hasExitTime) { m_hasExitTime = hasExitTime; return this; };
		CTransition* SetRelatedTo(bool relatedTo) { m_isRelatedTo = relatedTo; return this; }

		std::map<std::string, bool>& GetConditions() { return m_conditions; }
		std::string GetDestinationAnimationName() const { return m_dstAnimationName; }
		bool GetHasExitTime() const { return m_hasExitTime; }
		bool GetRelatedTo() const { return m_isRelatedTo; }
		bool GetConditionValue(std::string name) { return m_conditions[name]; };

		// Override
	private:
		void Update(DWORD dt) override {};
		void Render() override {}
	private:;
	};

	class CAnimator final : public CComponent
	{
		// Properties
	private:
		std::map<std::string, CAnimation*> m_Animations = {};
		std::map<std::string, std::list<CTransition*> > m_transitions = {};
		std::map<std::string, bool> m_boolConditions = {};
		CAnimation* m_pCurrentAnimation = nullptr;
		CAnimation* m_pRootAnimation = nullptr;

		// Cons / Des
	public:
		CAnimator() = default;
		CAnimator(const CAnimator& animator);
		CAnimator(CGameObject* game_object) : CComponent(game_object) {}
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init();
		void Release();

		//Getter / Setter
	private:
		CAnimator* AddAnimation(CAnimation* animation);
	public:
		CAnimator* AddAnimation(std::string animationName);
		CAnimator* AddTransition(std::string srcAnimationName, std::string dstAnimationName, bool hasExitTime = false,
				std::string conditionName = "", bool value = false, bool relatedTo = false);
		CAnimator* SetRootAnimation(std::string animationName);

		CAnimation *GetCurrentAnimation();
		CSprite *GetCurrentSprite();
		CTransition *GetTransition(std::string srcAnimationName, std::string dstAnimationName);

		CAnimator* AddBool(std::string name, bool value);
		CAnimator* SetBool(std::string name, bool value);
		bool GetBool(std::string name, bool defaultValue = false);

	public:
		void Update(DWORD dt) override;
		void Render() override;

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);
		CAnimator* Clone() override { return new CAnimator(*this); }
	};
}
