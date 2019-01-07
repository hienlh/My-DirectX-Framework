#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class HelitMissleController : public Framework::CMonoBehavior
{
private:
	int m_lifeTime = 5000;
	// To Clone Function
public:
	HelitMissleController() = default;
	HelitMissleController(const HelitMissleController &PC);
	HelitMissleController* Clone()  override;

	//Cons / Des
public:
	HelitMissleController(CGameObject* gameObject);
	~HelitMissleController();

	//Override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
