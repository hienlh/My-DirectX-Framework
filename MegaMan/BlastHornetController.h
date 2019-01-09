#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
#include <vector>
#include "Animator.h"
#include "Renderer.h"
#include "CanAttacked.h"
using namespace std;
using namespace Framework;
class BlastHornetController : public CMonoBehavior
{
public:
	Vector2 m_FlySpeed = Vector2(0.1, 0);
	CGameObject* m_target = nullptr;

	bool m_startBombing = false;
	bool m_targeting = false;
	bool m_attacking = false;
	bool m_isTargeted = false;
	bool m_startAttack = false;

	float m_flySpeed = 0.1;
	int attackID = 0; //save attack ID (1,5:Attack(); 2->4:Bomb(); 6->10:Shoot()

	Vector2 InitPos = {};
	DWORD waitTime = 0;
	int waitTimeWhenDie = 1000;
	DWORD startFly = 0;
	int targetTime = 0;
	CGameObject* pBullet = nullptr;
	bool isCollision = false;

	float m_limitedSize = 10;
	float top = 1807;
	float left = 7695;
	float bottom = 1930;
	float right = 7920;
	Bound m_topLeft = Bound(top, left, top + m_limitedSize, left + m_limitedSize);
	Bound m_topRight = Bound(top, right - m_limitedSize, top + m_limitedSize, right);
	Bound m_bottomLeft = Bound(bottom - m_limitedSize, left, bottom, left + m_limitedSize);
	Bound m_bottomRight = Bound(bottom - m_limitedSize, right - m_limitedSize, bottom, right);

	Vector2 m_lastPosition = {};
	Vector2 m_lastVelocity = {};
	DWORD m_lastStartFly = {};
	vector<CGameObject*> child1Pool = {};

	CTransform* transform = nullptr;
	CAnimator* anim = nullptr;
	CRigidbody* rigid = nullptr;
	CRenderer* renderer = nullptr;
	CBoxCollider* collider = nullptr;

	// To Clone Function
public:
	BlastHornetController() = default;
	BlastHornetController(const BlastHornetController &PC);
	BlastHornetController* Clone()  override;

	//Cons / Des
public:
	BlastHornetController(CGameObject* gameObject);

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD& dt) override;

	//Function
	void Shoot(const Vector2 &myPos, const Vector2 &targetPos);
	void Bomb(const Vector2 &myPos, const Vector2 &targetPos) const;
	void Attack(const Vector2 &myPos, const Vector2 &targetPos);
	Vector2 CalculateVelocity(const Vector2 &myPos, const Vector2 &targetPos, const float &size) const;
	void AddChild(CGameObject* child);
	CGameObject* GetDeactivateChild();
	Vector2 CalculatePosition(const float& dt, const float& velocity, const float& a) const;
};

