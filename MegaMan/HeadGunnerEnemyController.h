#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class HeadGunnerEnemyController : public CMonoBehavior
{
private:
	float m_speed = 0;
	CGameObject* m_target = nullptr;
	DWORD m_reloadTime = 0;

	// To Clone Function
private:
	HeadGunnerEnemyController() = default;
	HeadGunnerEnemyController(const HeadGunnerEnemyController &PC);
	HeadGunnerEnemyController* Clone() override { return new HeadGunnerEnemyController(*this); }

	HeadGunnerEnemyController& operator=(const CComponent& component) override;

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
	void Update(const DWORD &dt) override;
	void Render() override;

};