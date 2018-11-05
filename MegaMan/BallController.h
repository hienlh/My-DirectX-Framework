#pragma once
<<<<<<< HEAD:MegaMan/BallController.h
#include "../Framework/Component.h"
#include "../Framework/MonoBehavior.h"

using namespace Framework;

class BallController : public CMonoBehavior
=======
#include "stdafx.h"
#include "Component.h"

namespace Megaman
>>>>>>> origin/dev:MegaMan/MarioController.h
{
	class MarioController : public Framework::CComponent
	{
		float width, height;
		Vector2 pos;

<<<<<<< HEAD:MegaMan/BallController.h
public:
	BallController(CGameObject *game_object);
	~BallController() = default;

public:
	void Update(DWORD dt) override;
	void Render() override;

	void OnCollisionEnter(CCollision* collision) override;
};
=======
	public:
		Framework::CGameObject* leftBlock;
		Framework::CGameObject* rightBlock;

	public:
		MarioController(Framework::CGameObject *game_object);
		~MarioController() = default;
>>>>>>> origin/dev:MegaMan/MarioController.h

	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}
