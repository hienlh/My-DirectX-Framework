#pragma once
#include "MonoBehavier.h"
#include "Renderer.h"

class HealthValueController : public Framework::CMonoBehavior
{
private:
	Framework::CGameObject* m_target = nullptr;
	float m_preRatio = 1;

public:
	HealthValueController(const HealthValueController& hv);

	explicit HealthValueController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject) {}

public:
	void Update(DWORD dt) override;
	HealthValueController* Clone() override { return new HealthValueController(*this); }

public:
	HealthValueController* SetTarget(Framework::CGameObject* object) { m_target = object; return this; }
};
