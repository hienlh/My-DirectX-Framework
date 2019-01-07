#pragma once
#include "MonoBehavier.h"
#include "Animator.h"

class CarryAimController : public Framework::CMonoBehavior
{
private:
	Framework::CAnimator* anim = nullptr;
	Framework::CTransform* transform = nullptr;
	Framework::CGameObject* parent = nullptr;

	Framework::CGameObject* m_pBox = nullptr;

	bool m_moveIn = false;
	bool m_moveOut = false;

	Vector2 m_destination = { 0,0 };

public:
	CarryAimController(const CarryAimController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
		m_moveIn = monoBehavior.m_moveIn;
		m_moveOut = monoBehavior.m_moveOut;
		m_destination = monoBehavior.m_destination;
	}

	explicit CarryAimController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	CarryAimController& operator=(const CComponent& component) override;

	CarryAimController* Clone() override { return new CarryAimController(*this); }

	void Start() override;
	void Update(const DWORD& dt) override;

	void MoveIn(const Vector2& destination);
	void MoveOut() { m_moveOut = true; }

	bool haveBox();
};
