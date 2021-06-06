#pragma once
#include "MonoBehavier.h"

class BoxEndController2 : public Framework::CMonoBehavior
{
public:
	BoxEndController2(const BoxEndController2& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit BoxEndController2(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	BoxEndController2& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		if (const auto pMet = dynamic_cast<const BoxEndController2*>(&component))
		{
		}

		return *this;
	}

	CMonoBehavior* Clone() override { return new BoxEndController2(*this); }

	void Update(const DWORD& dt) override;
	void OnTriggerEnter(Framework::CCollision* collision) override;
	void OnCollisionEnter(Framework::CCollision* collision) override;

};
