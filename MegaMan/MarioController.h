#pragma once
#include "../Framework/Component.h"
#include "../Framework/MonoBehavior.h"

using namespace Framework;

class MarioController : public CMonoBehavior
{
	float width, height;
	Vector2 pos;

public:
	CGameObject* leftBlock;
	CGameObject* rightBlock;

public:
	MarioController(CGameObject *game_object);
	~MarioController() = default;

public:
	void Update(DWORD dt) override;
	void Render() override;

	void OnCollisionEnter(CCollision* collision) override;
};

