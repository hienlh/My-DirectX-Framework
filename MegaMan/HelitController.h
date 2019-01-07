#pragma once
#include "MonoBehavier.h"
using namespace Framework;using namespace Framework;
class HelitController : public Framework::CMonoBehavior
{
private:
	int m_reloadTime = 2000;
	Vector2 m_missleVelocity = Vector2(0.1, 0);
	// To Clone Function
public:
	HelitController() = default;
	HelitController(const HelitController &PC);
	HelitController* Clone()  override;
	//Cons / Des
public:
	HelitController(CGameObject* gameObject);
	~HelitController();

	//Override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
