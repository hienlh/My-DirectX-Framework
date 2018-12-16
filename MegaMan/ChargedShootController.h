#pragma once
#include "MonoBehavier.h"
using namespace Framework;

class ChargedShootController : public CMonoBehavior
{
	// To Clone Function
private:
	ChargedShootController(const ChargedShootController &PC) : CMonoBehavior(PC) {}
	ChargedShootController* Clone() const override { return new ChargedShootController(*this); }

	//Cons / Des
public:
	ChargedShootController() = default;
	~ChargedShootController() = default;
	ChargedShootController(CGameObject *gameObject) : CMonoBehavior(gameObject) {}

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

