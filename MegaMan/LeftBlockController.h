#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
using namespace Framework;

class LeftBlockController : public CMonoBehavior
{
	//Cons / Des
private:
	LeftBlockController() = default;
public:
	LeftBlockController(CGameObject *gameObject);
	~LeftBlockController() = default;

public:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

private:
	//void Move();
};