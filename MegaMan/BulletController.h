#pragma once
#include <MonoBehavier.h>
using namespace  Framework;
class BulletController : public CMonoBehavior
{
public:
	//Cons / Des
public:
	BulletController(CGameObject *gameObject);
	~BulletController() = default;

private:
	void Update(DWORD dt) override;
	void Render() override;
};

