#pragma once
#include <MonoBehavier.h>
using namespace  Framework;
class BulletController : public CMonoBehavior
{
	//Cons / Des
public:
	BulletController(CGameObject *gameObject);
	~BulletController() = default;

private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};

