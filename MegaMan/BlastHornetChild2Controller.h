#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class BlastHornetChild2Controller : public Framework::CMonoBehavior
{
private:
	CGameObject* m_target;
	CGameObject* m_parent;
	int lifeTime;
	// To Clone Function
public:
	BlastHornetChild2Controller() = default;
	BlastHornetChild2Controller(const BlastHornetChild2Controller &PC);
	BlastHornetChild2Controller* Clone()  override;

	//Getter Setter
public:
	void SetTarget(CGameObject* target) { m_target = target; }
	void SetParent(CGameObject* parent) { m_parent = parent; }
	void SetAliveTime(int time) { lifeTime = time; }
	//Cons / Des
public:
	BlastHornetChild2Controller(CGameObject* gameObject);
	~BlastHornetChild2Controller();

	//Override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	//
public:
	void Explosive();
};

