#pragma once
#include <MonoBehavier.h>
using namespace Framework;
class GenjiBosController :public CMonoBehavior
{
public:
	CGameObject *m_light;
	float m_startTime= GetTickCount();
	CGameObject* m_shurikein;
public:
	GenjiBosController(CGameObject* gameObject);
	~GenjiBosController();

	//Overide
	void Update(DWORD dt) override;
	void Render() override;
};

