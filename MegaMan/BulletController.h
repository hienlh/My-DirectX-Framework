#pragma once
#include "MonoBehavier.h"
using namespace Framework;

class BulletController : public CMonoBehavior
{
private:
	DWORD m_liveTime = 0;
	int m_waitForCreateSmoke = 50;
	int m_currentWaitTime = 0;

	// To Clone Function
private:
	BulletController(const BulletController &BC);
	BulletController* Clone() override { return new BulletController(*this); }

	BulletController& operator=(const CComponent& component) override;

	//Cons / Des
public:
	BulletController() = default;
	~BulletController() = default;
	BulletController(CGameObject *gameObject) : CMonoBehavior(gameObject) {}

	//Override
private:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
	void Render() override;

	void SmokeEffect(const DWORD &dt);
};

