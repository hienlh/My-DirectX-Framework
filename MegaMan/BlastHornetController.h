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

	bool m_startBombing = true;
	bool m_targeting = false;
	bool m_attacking = false;

	bool m_isTargeted = false;
	float m_limitedSize = 10;
	float top = 1807;
	float left = 7695;
	float bottom = 1930;
	float right = 7920;
	float m_flySpeed = 0.1;
	Bound m_topLeft=Bound(top, left, top+ m_limitedSize, left+m_limitedSize);
	Bound m_topRight =Bound(top, right-m_limitedSize, top + m_limitedSize, right);
	Bound m_bottomLeft =Bound(bottom-m_limitedSize, left, bottom, left + m_limitedSize);
	Bound m_bottomRight =Bound(bottom - m_limitedSize, right - m_limitedSize, bottom, right);

	Vector2 m_lastPosition;
	Vector2 m_lastVelocity;

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
	// void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	
	//function
	void Shoot(Vector2 targetPos);
	Vector2 CalculateVelocity(Vector2 myPos, Vector2 targetPos, float size);
	void AddChild(CGameObject* child);
	CGameObject* GetDisactiveChild();
};

