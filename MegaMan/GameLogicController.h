#pragma once
#include "MonoBehavier.h"

class GameLogicController final : public Framework::CMonoBehavior
{
public:
	GameLogicController(const GameLogicController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit GameLogicController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	GameLogicController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		return *this;
	}

	CMonoBehavior* Clone() override { return new GameLogicController(*this); }

	void Start() override;
	void Update(const DWORD& dt) override;

};
