#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class BusterShotController : public Framework::CMonoBehavior
{
	float m_destroyTime = 1000;
	float m_liveTime = 0;

	// To Clone Function
private:
	BusterShotController() = default;
	BusterShotController(const BusterShotController &BC);
	BusterShotController* Clone() override { return new BusterShotController(*this); }

	//Getter / Setter
public:
	float GetDestroyTime() const { return m_destroyTime; }

	BusterShotController* SetDestroyTime(float time) { m_destroyTime = time; return this; }

	//Cons / Des
public:
	BusterShotController(CGameObject *gameObject);
	~BusterShotController() = default;

	//Override
private:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

