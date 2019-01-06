#pragma once
#include "MonoBehavier.h"
#include "Animator.h"
using namespace Framework;
class BlastHornetBulletController : public Framework::CMonoBehavior
{
private:
	CGameObject* m_target;
	CGameObject* m_parent;
	int m_flyTime = 5000;
	int m_targetTime = 3000;
	// To Clone Function
public:
	BlastHornetBulletController() = default;
	BlastHornetBulletController(const BlastHornetBulletController &PC);
	BlastHornetBulletController* Clone()  override;

	//Getter Setter
public:
	void SetTarget(CGameObject* target) { m_target = target; }
	void SetParent(CGameObject* parent) { m_parent = parent; }
	bool GetIstargeted() const { return m_pGameObject->GetComponent<CAnimator>()->GetBool("isTargeted"); }
	//Cons / Des
public:
	BlastHornetBulletController(CGameObject* gameObject);
	~BlastHornetBulletController();

	//Override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	
};
