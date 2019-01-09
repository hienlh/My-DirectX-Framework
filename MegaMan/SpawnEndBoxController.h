#pragma once
#include "MonoBehavier.h"

const int WAIT_TIME = 2000;

class SpawnEndBoxController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject* target = nullptr;

private:
	int m_waitTime = WAIT_TIME;

public:
	SpawnEndBoxController(const SpawnEndBoxController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit SpawnEndBoxController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	SpawnEndBoxController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		if (const auto pMet = dynamic_cast<const SpawnEndBoxController*>(&component))
		{
		}

		return *this;
	}

	CMonoBehavior* Clone() override { return new SpawnEndBoxController(*this); }

	void Update(const DWORD& dt) override;

};

