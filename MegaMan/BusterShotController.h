#pragma once
#include "MonoBehavier.h"
using namespace Framework;
class BusterShotController : public Framework::CMonoBehavior
{
	float m_destroyTime = 2000;
	float m_liveTime = 0;

	// To Clone Function
private:
	BusterShotController() = default;
	BusterShotController(const BusterShotController &BC);
	BusterShotController* Clone() override { return new BusterShotController(*this); }

	BusterShotController& operator=(const CComponent& component) override;

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
	void Update(const DWORD &dt) override;
	void Render() override;
public:
};

