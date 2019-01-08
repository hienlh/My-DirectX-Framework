#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class ChargeShotController : public Framework::CMonoBehavior
{
	float m_destroyTime = 2000;
	float m_liveTime = 0;
	bool isCollision = false;
	// To Clone Function
private:
	ChargeShotController() = default;
	ChargeShotController(const ChargeShotController &BC);
	ChargeShotController* Clone() override { return new ChargeShotController(*this); }

	ChargeShotController& operator=(const CComponent& component) override;

	//Getter / Setter
public:
	float GetDestroyTime() const { return m_destroyTime; }

	ChargeShotController* SetDestroyTime(float time) { m_destroyTime = time; return this; }

	//Cons / Des
public:
	ChargeShotController(CGameObject *gameObject);
	~ChargeShotController() = default;

	//Override
private:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
	void Render() override;
};
