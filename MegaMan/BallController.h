#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;
#define MEGAMAN_VELOCITY 0.1
#define MEGAMAN_DASH 0.2
#define MEGAMAN_JUMPFORCE 0.4

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
	bool m_isCollideWall = false;
	//Cons / Des
private:
	BallController() = default;
public:
	BallController(CGameObject *gameObject);
	~BallController() = default;

	int GetState() const { return m_state; }
	void SetState(int state);

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void OnCollisionStay(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
