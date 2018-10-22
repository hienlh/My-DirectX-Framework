#pragma once
#include "Collider.h"

using namespace Framework;

class CBoxCollider: public CCollider
{
private:
	Vector2 _size;
public:
	CBoxCollider(CGameObject* gameObject);
	~CBoxCollider() = default;

	//Override
public:
	void Update(DWORD dt) override;
	void Render() override;
};
