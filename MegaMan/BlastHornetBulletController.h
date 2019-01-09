#pragma once
#include "MonoBehavier.h"
#include "Animator.h"
using namespace Framework;
class BlastHornetBulletController : public Framework::CMonoBehavior
{
private:
	CGameObject* m_target = nullptr;
	CGameObject* m_parent = nullptr;
	int m_flyTime = 2000;
	int m_targetTime = 1000;

	CTransform* transform = nullptr;
	CRigidbody* rigid = nullptr;
	CAnimator* anim = nullptr;

	// To Clone Function
public:
	BlastHornetBulletController() = default;
	BlastHornetBulletController(const BlastHornetBulletController &PC);
	BlastHornetBulletController* Clone()  override;

	//Getter Setter
public:
	void SetTarget(CGameObject* target) { m_target = target; }
	void SetParent(CGameObject* parent) { m_parent = parent; }
	bool GetIsTargeted() const { return m_pGameObject->GetComponent<CAnimator>()->GetBool("isTargeted"); }
	//Cons / Des
public:
	BlastHornetBulletController(CGameObject* gameObject);

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD& dt) override;

};
