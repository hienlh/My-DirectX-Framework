#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class PlayerController : public CMonoBehavior
{
public:
	CGameObject* m_Power = nullptr;

private:
	float m_speed = 0;
	DWORD m_wasHitTime = 0;

	// To Clone Function
private:
	PlayerController() = default;
	PlayerController(const PlayerController &PC) : CMonoBehavior(PC) { m_speed = PC.m_speed; };
	PlayerController* Clone() const override { return new PlayerController(*this); }

	//Cons / Des
public:
	PlayerController(CGameObject *gameObject) : CMonoBehavior(gameObject) {};
	~PlayerController() = default;

	//Getter / Setter
public:
	PlayerController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void OnTriggerEnter(CCollision* collision) override;
	void OnTriggerExit(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

};
