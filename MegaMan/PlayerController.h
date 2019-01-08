#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
#include "Animator.h"
#include "Renderer.h"
#include "Input.h"
#include "CameraController.h"
#include "CanAttacked.h"

using namespace Framework;

#define Jump_Velocity .2

class PlayerController : public CMonoBehavior
{
public:
	CGameObject* m_Power = nullptr;
	CGameObject* m_DieEffect = nullptr;
	CGameObject* m_DashFullEffectEffect = nullptr;
	CGameObject* m_DashEffect = nullptr;
	CGameObject* m_GenjiBos = nullptr;
	CGameObject* m_DoubleJumpEffect = nullptr;

	CGameObject* pBuilding = nullptr;
	CGameObject* pBlastHornet = nullptr;

private:
	float m_speed = 0;
	bool m_onMachine = false;
	bool m_onScrollWheelLeft = false;
	bool m_onScrollWheelRight = false;
	bool m_canMove = true;
	bool m_canAction = true;
	bool m_isAlive = true;
	bool m_isFightingBoss = false;
	DWORD m_pressTime = 0;

	CAnimator * anim = nullptr;
	CTransform * transform = nullptr;
	CRigidbody * rigidBody = nullptr;
	CRenderer * renderer = nullptr;
	CInput* input = nullptr;
	CameraController* mainCamera = nullptr;

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
	bool GetIsAlive() const { return m_isAlive; }

	//Override
private:
	void Start() override;
	void OnCollisionEnter(CCollision* collision) override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;

	//Method
public:
	void Action(DWORD dt);
	void Move() const;
	void Dash(bool isLeft) const;
	void Shoot() const;
	void CheckFightBoss();
	void PassBuilding();
	
};
