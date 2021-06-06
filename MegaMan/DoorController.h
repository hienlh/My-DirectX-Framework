#pragma once
#include "MonoBehavier.h"
#include "CameraController.h"
#include "Animator.h"

class DoorController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject* pBoss = nullptr;

private:
	Framework::CGameObject* m_target = nullptr;

	Framework::CAnimator* anim = nullptr;
	Framework::CBoxCollider* collider = nullptr;

public:
	DoorController(const DoorController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit DoorController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void Start() override;
	void OnTriggerEnter(Framework::CCollision* collision) override;
	void Update(const DWORD &dt) override;

	DoorController* Clone() override { return new DoorController(*this); }
};
