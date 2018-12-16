#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
using namespace Framework;
class BlastHornetController : public Framework::CMonoBehavior
{
public:
	Vector2 m_FlySpeed = Vector2(0.1,0);
	CGameObject* m_target;

	// To Clone Function
public:
	BlastHornetController() = default;
	BlastHornetController(const BlastHornetController &PC);
	BlastHornetController* Clone() const override;
	
	//Cons / Des
public:
	BlastHornetController(CGameObject* gameObject);
	~BlastHornetController();
	
	//Override
private:
	// void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

