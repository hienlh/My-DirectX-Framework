#pragma once
#include "MonoBehavier.h"

class BoxController : public Framework::CMonoBehavior
{
public:
	BoxController(const CMonoBehavior& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit BoxController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}
	BoxController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		return *this;
	}

	BoxController* Clone() override { return new BoxController(*this); }

	void Update(const DWORD& dt) override;

};
