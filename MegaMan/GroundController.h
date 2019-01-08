#pragma once
#include "MonoBehavier.h"

class GroundController : public Framework::CMonoBehavior
{//Cons / Des
private:
	GroundController() = default;
public:
	GroundController(const GroundController& gc) : CMonoBehavior(gc) {};
	GroundController(Framework::CGameObject *gameObject) : CMonoBehavior(gameObject){}
	~GroundController() = default;

public:
	void OnCollisionEnter(Framework::CCollision* collision) override;
	void Update(const DWORD &dt) override;
	void Render() override;

	GroundController* Clone() override { return new GroundController(*this); }
	
};
