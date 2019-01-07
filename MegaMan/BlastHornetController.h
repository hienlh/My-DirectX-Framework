#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
#include <vector>
using namespace std;
using namespace Framework;
class BlastHornetController : public Framework::CMonoBehavior
{
public:
	Vector2 m_FlySpeed = Vector2(0.1,0);
	CGameObject* m_target;

	bool m_startBombing = false;
	bool m_targeting = false;
	bool m_attacking = false;
	bool m_isTargeted = false;
	bool m_startAttack = false;

	float m_flySpeed = 0.1;
	int attackID=0; //save attack ID (1,5:Attack(); 2->4:Bomb(); 6->10:Shoot()

	Vector2 InitPos;
	DWORD waitTime = 0;
	DWORD startFly = 0;
	int targetTime = 0;
	CGameObject* pBullet = nullptr;
	bool isCollision = false;

	float m_limitedSize = 10;
	float top = 1807;
	float left = 7695;
	float bottom = 1930;
	float right = 7920;
	Bound m_topLeft=Bound(top, left, top+ m_limitedSize, left+m_limitedSize);
	Bound m_topRight =Bound(top, right-m_limitedSize, top + m_limitedSize, right);
	Bound m_bottomLeft =Bound(bottom-m_limitedSize, left, bottom, left + m_limitedSize);
	Bound m_bottomRight =Bound(bottom - m_limitedSize, right - m_limitedSize, bottom, right);

	Vector2 m_lastPosition;
	Vector2 m_lastVelocity;
	DWORD m_lastStartFly;
	vector<CGameObject*> child1Pool;
	
	// To Clone Function
public:
	BlastHornetController() = default;
	BlastHornetController(const BlastHornetController &PC);
	BlastHornetController* Clone()  override;
	
	//Cons / Des
public:
	BlastHornetController(CGameObject* gameObject);
	~BlastHornetController();
	
	//Override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	
	//Function
	void Shoot(Vector2 myPos, Vector2 targetPos);
	void Bomb(Vector2 myPos, Vector2 targetPos);
	void Attack(Vector2 myPos, Vector2 targetPos);
	Vector2 CalculateVelocity(Vector2 myPos, Vector2 targetPos, float size);
	void AddChild(CGameObject* child);
	CGameObject* GetDisactiveChild();
	Vector2 CalculatePosition(float dt, float velocity, float a);
};

