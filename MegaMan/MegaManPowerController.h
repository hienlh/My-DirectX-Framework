#pragma once
#include "MonoBehavier.h"
using namespace Framework;

class MegaManPowerController :public CMonoBehavior
{

public:
	MegaManPowerController(CGameObject* gameObject);
	~MegaManPowerController();
private:
	void Update(DWORD dt) override;
	void Render() override;
};

