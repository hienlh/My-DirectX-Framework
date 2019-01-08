#pragma once
#include "Component.h"
#include "PhysicObserver.h"
#include "GameObserver.h"
#include "GameManager.h"

namespace Framework {
	class CMonoBehavior : public CComponent, public CPhysicObserver, public CGameObserver
	{

	private:
		CMonoBehavior() = default;
	public:
		CMonoBehavior(const CMonoBehavior &monoBehavior) : CComponent(monoBehavior), CGameObserver(monoBehavior)
		{
			CGameObserver::WakeUp();
		}

		explicit CMonoBehavior(CGameObject* gameObject) : CComponent(gameObject), CGameObserver(CGameManager::GetInstance())
		{
			CGameObserver::WakeUp();
		}

		virtual ~CMonoBehavior() = default;

		void Update(const DWORD &dt) override {}
		void Render() override {}
		CMonoBehavior* Clone() override = 0;

		virtual CMonoBehavior& operator=(const CComponent& component) override { (*this).CComponent::operator=(component); return *this; }
	};
}
