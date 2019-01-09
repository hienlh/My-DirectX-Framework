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
	HelitMissleController& operator=(const CComponent& component) override;

	//Cons / Des
public:
	HelitMissleController(CGameObject* gameObject);
	~HelitMissleController() = default;

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
};