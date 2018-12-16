#pragma once
#include "MonoBehavier.h"

class MachineController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject *m_player = nullptr;
public:
	explicit MachineController(const CMonoBehavior& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit MachineController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void OnCollisionEnter(Framework::CCollision* collision) override;

public:
	void Update(DWORD dt) override;
};
