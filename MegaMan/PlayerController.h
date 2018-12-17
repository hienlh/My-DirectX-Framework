#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class PlayerController : public CMonoBehavior
{
public:
	CGameObject* m_Power = nullptr;
	CGameObject* m_GenjiBos = nullptr;

private:
	float m_speed = 0;

	// To Clone Function
private:
	PlayerController() = default;
	PlayerController(const PlayerController &PC);
	PlayerController* Clone() const override;

	//Cons / Des
public:
	PlayerController(CGameObject *gameObject);
	~PlayerController() = default;

	//Getter / Setter
public:
	PlayerController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

	//Method
public:
	void Shoot();

};
