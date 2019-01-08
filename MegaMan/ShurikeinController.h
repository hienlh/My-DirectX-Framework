#pragma once
#include <MonoBehavier.h>
#include "Animator.h"
#include <ctime>
#include <cstdlib>
using namespace Framework;
class ShurikeinController : public CMonoBehavior
{
private:
	Rect rectlimit = {};
public:
	//CGameObject *m_shurikein;
	float m_startTime = 0;
	float m_waitForChangeColor = 0;

public:
	ShurikeinController(const ShurikeinController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}
	ShurikeinController(CGameObject* gameObject);

	ShurikeinController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		return *this;
	}

	//Overide
	void OnTriggerEnter(CCollision *collision) override;
	void Update(const DWORD &dt) override;
	ShurikeinController* Clone() override { return new ShurikeinController(*this); };
};

