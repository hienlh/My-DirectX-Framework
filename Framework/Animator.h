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
		explicit CTransition(const std::string &name) { m_dstAnimationName = name; }
		CTransition(const CTransition& transition);
		~CTransition() override = default;

	public:
		CTransition* SetCondition(const std::string &conditionName, const bool &value) { m_conditions[conditionName] = value; return this; }
		CTransition* SetHasExitTime(const bool &hasExitTime) { m_hasExitTime = hasExitTime; return this; };
		CTransition* SetRelatedTo(const bool &relatedTo) { m_isRelatedTo = relatedTo; return this; }

		const std::map<std::string, bool>& GetConditions() const { return m_conditions; }
		const std::string& GetDestinationAnimationName() const { return m_dstAnimationName; }
		const bool& GetHasExitTime() const { return m_hasExitTime; }
		const bool& GetRelatedTo() const { return m_isRelatedTo; }
		const bool& GetConditionValue(const std::string& name) { return m_conditions[name]; };

		// Override
	private:
		void Update(const DWORD &dt) override {}
		void Render() override {}
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
		explicit CAnimator(CGameObject* game_object) : CComponent(game_object) {}
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init();
		void Release();

		//Getter / Setter
	private:
		CAnimator* AddAnimation(CAnimation* animation);
	public:
		CAnimator* AddAnimation(const std::string &animationName);
		CAnimator* AddTransition(const std::string& srcAnimationName, const std::string& dstAnimationName,
		                         const bool& hasExitTime = false, const std::string& conditionName = "",
		                         const bool& value = false, const bool& relatedTo = false);
		CAnimator* SetRootAnimation(const std::string &animationName);

		CAnimation *GetCurrentAnimation();
		CSprite *GetCurrentSprite();
		CTransition *GetTransition(const std::string& srcAnimationName, const std::string& dstAnimationName);

		CAnimator* AddBool(const std::string& name, const bool& value);
		CAnimator* SetBool(const std::string& name, const bool& value);
		bool GetBool(std::string name, bool defaultValue = false);

	public:
		void Update(const DWORD &dt) override;
		void Render() override;
		CAnimator* Clone() override { return new CAnimator(*this); }

		CAnimator& operator=(const CComponent& component) override;

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);
	};
}
