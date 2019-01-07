#pragma once
#include "MonoBehavier.h"
#include "Animator.h"

class MetaCapsuleController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject* player = nullptr;

private:
	Framework::CAnimator* anim = nullptr;
	Framework::CBoxCollider* collider = nullptr;
	Framework::CTransform* transform = nullptr;

	int m_waitTime = 1000;
	bool m_fired = false;

	Framework::CGameObject* m_bullet = nullptr;
	Framework::CGameObject* m_bulletPrefab = nullptr;

public:
	MetaCapsuleController(const MetaCapsuleController& monoBehavior);

	explicit MetaCapsuleController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	MetaCapsuleController& operator=(const CComponent& component) override;

	CMonoBehavior* Clone() override { return new MetaCapsuleController(*this); }

	void Start() override;
	void Update(const DWORD& dt) override;

	void Fire();
};
