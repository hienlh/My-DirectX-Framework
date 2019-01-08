#pragma once
#include "MonoBehavier.h"

class BoxEndController : public Framework::CMonoBehavior
{
public:
	BoxEndController(const BoxEndController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit BoxEndController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	BoxEndController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		if (const auto pMet = dynamic_cast<const BoxEndController*>(&component))
		{
		}

		return *this;
	}

	CMonoBehavior* Clone() override { return new BoxEndController(*this); }

	void Update(const DWORD& dt) override;

};
