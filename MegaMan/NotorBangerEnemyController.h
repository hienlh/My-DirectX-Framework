#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class NotorBangerEnemyController : public CMonoBehavior
{
private:
	float m_speed = 0;
	CGameObject* m_target = nullptr;

	// To Clone Function
private:
	NotorBangerEnemyController() = default;
	NotorBangerEnemyController(const NotorBangerEnemyController &PC) : CMonoBehavior(PC) { m_speed = PC.m_speed; }
	NotorBangerEnemyController* Clone() override { return new NotorBangerEnemyController(*this); }

	//Cons / Des
public:
	NotorBangerEnemyController(CGameObject *gameObject) : CMonoBehavior(gameObject) {};
	~NotorBangerEnemyController() = default;

	//Getter / Setter
public:
	NotorBangerEnemyController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }
	void SetTarget(CGameObject* targer) { m_target = targer; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

};

