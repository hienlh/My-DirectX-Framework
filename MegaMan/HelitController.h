#pragma once
#include "MonoBehavier.h"
#include "Renderer.h"
using namespace Framework;

class HelitController : public CMonoBehavior
{
private:
	int m_reloadTime = 2000;
	Vector2 m_missleVelocity = Vector2(0.1, 0);

	CTransform* transform = nullptr;
	CRenderer* renderer = nullptr;
	CRigidbody* rigid = nullptr;

	CGameObject* m_target = nullptr;

	float m_limitTop = 0;
	float m_limitBottom = 0;

	// To Clone Function
public:
	HelitController() = default;
	HelitController(const HelitController &PC);
	HelitController* Clone()  override;
	HelitController& operator=(const CComponent& component) override;

	HelitController* SetLimitDistance(const int& distance = 20);

	//Cons / Des
public:
	HelitController(CGameObject* gameObject);
	~HelitController() = default;

	HelitController* SetTarget(CGameObject* target) { m_target = target; return this; }

	//Override
public:
	void Start() override;
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
};