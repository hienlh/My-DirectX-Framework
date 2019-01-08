#pragma once
#include "MonoBehavier.h"

class HealItemController : public Framework::CMonoBehavior
{
private:
	int m_healValue = 0;
public:
	bool isCollision = false;
	//Setter Getter
public:
	void SetHealValue(int value) { m_healValue = value; }
	int GetHealValue() { return m_healValue; }

public:
	HealItemController(const HealItemController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit HealItemController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void OnCollisionEnter(Framework::CCollision* collision) override;
	void Update(const DWORD &dt) override;

	HealItemController* Clone() override { return new HealItemController(*this); }
};
