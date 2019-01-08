#pragma once
#include "MonoBehavier.h"
#include "ResourceManager.h"
#include "Macros.h"

class DashFullEffect : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject* m_dashSmokeEffect = nullptr;
private:
	bool m_isDashing = false;
	bool m_isLeft = false;
	int m_waitForCreateSmoke = 50;
	int m_currentWaitTime = 0;

public:
	DashFullEffect(const DashFullEffect& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
		m_dashSmokeEffect = monoBehavior.m_dashSmokeEffect;
		m_waitForCreateSmoke = monoBehavior.m_waitForCreateSmoke;
		m_isDashing = monoBehavior.m_isDashing;
		m_isLeft = monoBehavior.m_isLeft;
	}

	explicit DashFullEffect(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
		auto resource = Framework::CResourceManager::GetInstance();
		m_dashSmokeEffect = resource->GetPrefab(Prefab_Effect_SmokeDash);
	}

	//Getter Setter
public:
	DashFullEffect* SetIsLeft(const bool& isLeft) { m_isLeft = isLeft; return this; }
	DashFullEffect* SetIsDashing(const bool& isDashing) { m_isDashing = isDashing; return this; }

public:
	void Update(const DWORD &dt) override;

	DashFullEffect* Clone() override { return new DashFullEffect(*this); }

	void CreateDash() const;
	void CreateSmoke();
};
