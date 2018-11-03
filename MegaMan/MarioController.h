#pragma once
#include "stdafx.h"
#include "Component.h"

namespace Megaman
{
	class MarioController : public Framework::CComponent
	{
		float width, height;
		Vector2 pos;

	public:
		Framework::CGameObject* leftBlock;
		Framework::CGameObject* rightBlock;

	public:
		MarioController(Framework::CGameObject *game_object);
		~MarioController() = default;

	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}
