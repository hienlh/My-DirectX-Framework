#pragma once
#include "MonoBehavier.h"
#include "Renderer.h"
using namespace Framework;

class HelitController : public Framework::CMonoBehavior
{
private:
	int m_reloadTime = 2000;
	Vector2 m_missleVelocity = Vector2(0.1, 0);

	CTransform* transform = nullptr;
	CRenderer* renderer = nullptr;

	// To Clone Function
public:
	HelitController() = default;
	HelitController(const HelitController &PC);
	HelitController* Clone()  override;
	HelitController& operator=(const CComponent& component) override;

	//Cons / Des
public:
	HelitController(CGameObject* gameObject);
	~HelitController() = default;

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
};