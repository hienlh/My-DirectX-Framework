#pragma once
#include <MonoBehavier.h>
using namespace  Framework;
class BulletManagerController : public CMonoBehavior
{
public:
	//Cons / Des
public:
	BulletManagerController(CGameObject *gameObject);
	~BulletManagerController() = default;

private:
	void Update(DWORD dt) override;
	void Render() override;
};

