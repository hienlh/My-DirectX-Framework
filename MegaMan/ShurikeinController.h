#pragma once
#include <MonoBehavier.h>
using namespace Framework;
class ShurikeinController : public CMonoBehavior
{
public:
	CGameObject *m_shurikein;
	float m_startTimeShurikein = 0;
public:
	ShurikeinController(CGameObject* gameObject);
	~ShurikeinController();

	//Overide
	void Update(DWORD dt) override;
	void Render() override;
};

