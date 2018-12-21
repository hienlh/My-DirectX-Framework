#pragma once
#include <MonoBehavier.h>
using namespace Framework;
class GenjiBosController :public CMonoBehavior
{
public:
	CGameObject *m_light;
	float m_startTime = 0;
	CGameObject* m_shurikein;
	CGameObject *m_target;
public:
	GenjiBosController(CGameObject* gameObject);
	~GenjiBosController();

	//Overide
	void Update(DWORD dt) override;
	void Render() override;
};

