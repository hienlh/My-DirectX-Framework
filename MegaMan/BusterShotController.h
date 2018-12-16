#pragma once
#include "MonoBehavier.h"
using namespace Framework;

class BusterShotController : public CMonoBehavior
{
	// To Clone Function
private:
	BusterShotController(const BusterShotController &PC) : CMonoBehavior(PC) {}
	BusterShotController* Clone() const override { return new BusterShotController(*this); }

	//Cons / Des
public:
	BusterShotController() = default;
	~BusterShotController() = default;
	BusterShotController(CGameObject *gameObject) : CMonoBehavior(gameObject) {}

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

