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

	class CTransition
	{
	private:
		CWString m_dstStateName;
		std::map<CWString, bool> m_conditions;

	public:
		CTransition(CWString name) { m_dstStateName = name; }

	public:
		void SetCondition(CWString conditionName, bool value) { m_conditions[conditionName] = value; }
		std::map<CWString, bool>& GetMapCondition() { return m_conditions; }
		CWString GetDestinationStateName() { return m_dstStateName; }
	};

	class CAnimator final : public CComponent
	{
		// Properties
	private:
		std::map<LPCWSTR, CState*> m_states = {};
		std::map<LPCWSTR, std::list<CTransition*> > m_transitions;
		std::map<LPCWSTR, bool> m_boolConditions;

		CState* m_currentState = nullptr;
		//DWORD m_stateCode = 0;

		// Cons / Des
	public:
		CAnimator() = default;
		CAnimator(CGameObject* gameObject) : CComponent(gameObject) {}
		virtual ~CAnimator() = default;

		// Internal methods
	private:
		bool Init();
		void Release();

		// Getter / Setter
	public:
		bool AddState(LPCWSTR stateName);
		bool SetCurrentState(LPCWSTR stateName);
		CTransition* AddTransition(LPCWSTR srcStateName, LPCWSTR dstStateName);

		//void SetStateCode(DWORD stateCode) { m_stateCode = stateCode; };
		
		bool AddBool(LPCWSTR name, bool value);
		bool SetBool(LPCWSTR name, bool value);
		bool GetBool(LPCWSTR name);

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CAnimator* Instantiate();
		static void Destroy(CAnimator* &instance);
	};
}
