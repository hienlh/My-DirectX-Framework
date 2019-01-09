#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
#include "Animator.h"
#include "Renderer.h"
#include "Input.h"
#include "CameraController.h"

using namespace Framework;


class PlayerController : public CMonoBehavior
{
public:
	CGameObject* m_Power = nullptr;
	CGameObject* m_DieEffect = nullptr;
	CGameObject* m_DashFullEffectEffect = nullptr;
	CGameObject* m_DashEffect = nullptr;
	CGameObject* m_DoubleJumpEffect = nullptr;

	CGameObject* pBuilding = nullptr;
	CGameObject* pGenjibo = nullptr;
	CGameObject* pShurikein = nullptr;
	CGameObject* pBlastHornet = nullptr;

private:
	CGameObject* m_pNotors[14] = {};
	CGameObject* m_pHeads[8] = {};
	CGameObject* m_pHelits[4] = {};

	CGameObject* m_pNotorPrefab = nullptr;
	CGameObject* m_pHeadPrefab = nullptr;
	CGameObject* m_pHelitPrefab = nullptr;

	float m_speed = 0;
	bool m_onMachine = false;
	bool m_canMove = true;
	bool m_canAction = true;
	bool m_isAlive = true;
	bool m_isFightingBoss = false;
	DWORD m_pressTime = 0;
	bool m_skyWalked = false;
	int m_waitDie = 1000;

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
	void Action(const DWORD &dt);
	void Move();
	void Dash(bool isLeft) const;
	void Shoot() const;
	void CheckFightBoss();
	void CheckEnemies();

};
