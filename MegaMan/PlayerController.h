#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
#include "Animator.h"
#include "Renderer.h"
#include "Input.h"

using namespace Framework;

#define Jump_Velocity 0.2

class PlayerController : public CMonoBehavior
{
public:
	CGameObject* m_Power = nullptr;
	CGameObject* m_GenjiBos = nullptr;

private:
	float m_speed = 0;
	bool m_onMachine = false;
	bool m_canMove = true;
	bool m_canAction = true;

	CAnimator * anim = nullptr;
	CTransform * transform = nullptr;
	CRigidbody * rigidBody = nullptr;
	CRenderer * renderer = nullptr;
	CInput* input = nullptr;

	// To Clone Function
private:
	PlayerController() = default;
	PlayerController(const PlayerController &PC);
	PlayerController* Clone() override { return new PlayerController(*this); }

	//Cons / Des
public:
	explicit PlayerController(CGameObject *gameObject);

	~PlayerController() = default;

	//Getter / Setter
public:
	PlayerController* SetSpeed(const float &speed) { m_speed = speed; return this; }
	PlayerController* SetCanMove(const bool &canMove) { m_canMove = canMove; return this; }
	PlayerController* SetCanAction(const bool &canAction) { m_canAction = canAction; return this; }

	float GetSpeed() const { return m_speed; }
	bool GetCanMove() const { return m_canMove; }
	bool GetCanAction() const { return m_canAction; }

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;

	//Method
public:
	void Action();
	void Move() const;
	void Shoot() const;

};
