#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class BusterShotController : public Framework::CMonoBehavior
{
	// To Clone Function
private:
	BusterShotController() = default;
	BusterShotController(const BusterShotController &PC);
	BusterShotController* Clone() const override;

	//Cons / Des
public:
	BusterShotController(CGameObject *gameObject);
	~BusterShotController() = default;

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

