#pragma once
#include <MonoBehavier.h>
#include "Animator.h"
#include <ctime>
#include <cstdlib>
using namespace Framework;
class ShurikeinController : public CMonoBehavior
{
private:
	Rect rectlimit;
public:
	//CGameObject *m_shurikein;
	float m_starttime = 0;
	float m_waitForChangeColor = 0;
	
public:
	ShurikeinController(CGameObject* gameObject);
	~ShurikeinController();

	//Overide
	void OnTriggerEnter(CCollision *collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	ShurikeinController* Clone() override { return new ShurikeinController(*this); };
};


