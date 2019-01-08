#pragma once
#include "MonoBehavier.h"

class ScrollingWheelController : Framework::CMonoBehavior
{
public:
	Framework::CGameObject *m_player = nullptr;
public:
	ScrollingWheelController(const ScrollingWheelController& mc)
		: CMonoBehavior(mc)
	{
		m_player = mc.m_player;
	}

	explicit ScrollingWheelController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	void OnCollisionEnter(Framework::CCollision* collision) override;

public:
	void Update(const DWORD &dt) override;

	ScrollingWheelController* Clone() override { return new ScrollingWheelController(*this); }
};
