#pragma once
#include "MonoBehavier.h"
#include "Header.h"
using namespace Framework;

class BulletController : public CMonoBehavior
{
private:
	DWORD m_liveTime = 0;

	// To Clone Function
private:
	BulletController(const BulletController &PC) : CMonoBehavior(PC) {}
	BulletController* Clone() const override { return new BulletController(*this); }

	//Cons / Des
public:
	BulletController() = default;
	~BulletController() = default;
	BulletController(CGameObject *gameObject) : CMonoBehavior(gameObject) {}

	//Override
private:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;


};

