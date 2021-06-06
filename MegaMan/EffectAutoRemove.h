#pragma once
#include "MonoBehavier.h"

class EffectAutoRemove : public Framework::CMonoBehavior
{
public:
	EffectAutoRemove(const EffectAutoRemove& ear)
		: CMonoBehavior(ear)
	{
	}

	explicit EffectAutoRemove(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	EffectAutoRemove* Clone() override { return new EffectAutoRemove(*this); }

	void Update(const DWORD &dt) override;
};
