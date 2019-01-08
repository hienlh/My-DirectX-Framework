#pragma once
#pragma once
#include "MonoBehavier.h"

class MachineController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject *m_player = nullptr;
public:
	MachineController(const MachineController& mc)
		: CMonoBehavior(mc)
	{
		m_player = mc.m_player;
	}

	explicit MachineController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void OnCollisionEnter(Framework::CCollision* collision) override;

public:
	void Update(const DWORD &dt) override;

	MachineController* Clone() override { return new MachineController(*this); }
};
