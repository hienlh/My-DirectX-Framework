#pragma once
#include "../Framework/Component.h"
#include "../Framework/MonoBehavior.h"

using namespace Framework;

class BallController : public CMonoBehavior
{
	float width, height;
	Vector2 pos;

public:
	CGameObject* leftBlock;
	CGameObject* rightBlock;

public:
	BallController(CGameObject *game_object);
	~BallController() = default;

public:
	void Update(DWORD dt) override;
	void Render() override;

	void OnCollisionEnter(CCollision* collision) override;
};

