#pragma once
#include "MonoBehavier.h"
#include "CameraController.h"

class DoorController : public Framework::CMonoBehavior
{
private:
	Framework::CGameObject* m_target = nullptr;

public:
	DoorController(const DoorController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit DoorController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void OnTriggerEnter(Framework::CCollision* collision) override;
	void Update(DWORD dt) override;

	DoorController* Clone() override { return new DoorController(*this); }
};
