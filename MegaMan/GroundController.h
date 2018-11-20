#pragma once
#include "MonoBehavier.h"

class GroundController : public Framework::CMonoBehavior
{//Cons / Des
private:
	GroundController() = default;
public:
	GroundController(Framework::CGameObject *gameObject) : CMonoBehavior(gameObject){}
	~GroundController() = default;

public:
	void OnCollisionEnter(Framework::CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
	
};
