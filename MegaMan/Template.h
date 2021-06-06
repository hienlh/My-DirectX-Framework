#pragma once
#include "MonoBehavier.h"

class Template : public Framework::CMonoBehavior
{
public:
	Template(const Template& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit Template(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	Template& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		if (const auto pMet = dynamic_cast<const Template*>(&component))
		{
		}

		return *this;
	}

	CMonoBehavior* Clone() override { return new Template(*this); }

	void Start() override;
	void Update(const DWORD& dt) override;
	
};
