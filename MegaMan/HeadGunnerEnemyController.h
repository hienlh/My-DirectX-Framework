#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class HeadGunnerEnemyController : public CMonoBehavior
{
private:
	float m_speed = 0;
	CGameObject* m_target = nullptr;

	// To Clone Function
private:
	HeadGunnerEnemyController() = default;
	HeadGunnerEnemyController(const HeadGunnerEnemyController &PC) : CMonoBehavior(PC) { m_speed = PC.m_speed; }
	HeadGunnerEnemyController* Clone() const override { return new HeadGunnerEnemyController(*this); }

	//Cons / Des
public:
	HeadGunnerEnemyController(CGameObject *gameObject) : CMonoBehavior(gameObject) {};
	~HeadGunnerEnemyController() = default;

	//Getter / Setter
public:
	HeadGunnerEnemyController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }
	void SetTarget(CGameObject* targer) { m_target = targer; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

};