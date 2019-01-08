#pragma once
#include "MonoBehavier.h"
#include "Animator.h"
#include "Renderer.h"
using namespace Framework;
class BlastHornetChild2Controller : public Framework::CMonoBehavior
{
private:
	CGameObject* m_target = nullptr;
	CGameObject* m_parent = nullptr;
	int lifeTime = 0;

	CAnimator* anim = nullptr;
	CTransform* transform = nullptr;
	CRigidbody* rigid = nullptr;
	CRenderer* renderer = nullptr;

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

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;

	//
public:
	void Explosive() const;
};

