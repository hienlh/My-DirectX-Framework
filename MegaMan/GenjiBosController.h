#pragma once
#include <MonoBehavier.h>
using namespace Framework;
class GenjiBosController :public CMonoBehavior
{
public:
	CGameObject *m_light = nullptr;
	float m_startTime = 0;
	CGameObject* m_shurikein = nullptr;
public:
	GenjiBosController(const GenjiBosController& gen);
	GenjiBosController(CGameObject* gameObject);
	~GenjiBosController() = default;

	//Overide
	void Update(DWORD dt) override;
	void Render() override;
	GenjiBosController* Clone() override { return new GenjiBosController(*this); }
};

