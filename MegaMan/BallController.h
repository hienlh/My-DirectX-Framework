#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class BallController : public CMonoBehavior
{
	//Cons / Des
private:
	BallController() = default;
public:
	BallController(CGameObject *gameObject);
	~BallController() = default;

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
