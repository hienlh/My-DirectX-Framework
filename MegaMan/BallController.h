﻿#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class BallController : public CMonoBehavior
{
public:
	enum State
	{
		JUMP = 1,
		MOVE_RIGHT = 2,
		MOVE_LEFT = 4,
		IDLE = 0,
		MOVE_DOWN = 8,
	};

private:
	int m_state;
	bool m_isCollideLadder = false;

	//Cons / Des
private:
	BallController() = default;
public:
	BallController(CGameObject *gameObject);
	~BallController() = default;

	int GetState() const { return m_state; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
