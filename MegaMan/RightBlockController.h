#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"
using namespace Framework;

class RightBlockController : public CMonoBehavior
{
//Cons / Des
private:
	RightBlockController() = default;
public:
	RightBlockController(CGameObject *gameObject);
	~RightBlockController() = default;

public:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

private:
	//void Move();
};