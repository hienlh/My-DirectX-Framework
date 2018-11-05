#pragma once
<<<<<<< HEAD
#include "../Framework/Component.h"
#include "../Framework/MonoBehavior.h"

using namespace Framework;

class BlockController : public CMonoBehavior
=======
#include "stdafx.h"
#include "Component.h"

namespace Megaman
>>>>>>> origin/dev
{
	class BlockController : public Framework::CComponent
	{
	private:
		bool m_isGoDown;
		bool m_isRight;
		Vector2 m_pos;
		Vector2 m_size;

		// Getter / Setter
	public:
		bool GetIsGoDown() const { return m_isGoDown; }
		bool GetIsRight() const { return m_isRight; }

		void SetIsGoDown(bool isGoDown) { m_isGoDown = isGoDown; }
		void SetIsRight(bool isRight) { m_isRight = isRight; }
		void SetAllParameters(bool isGoDown, bool isRight) { SetIsGoDown(isGoDown); SetIsRight(isRight); }

	public:
		BlockController(Framework::CGameObject *game_object);
		~BlockController() = default;

	public:
		void Update(DWORD dt) override;
		void Render() override;

	private:
		void Move();
	};
}