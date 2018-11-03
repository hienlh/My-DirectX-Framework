#pragma once
#include "stdafx.h"
#include "Component.h"

namespace Megaman
{

	class CameraController : public Framework::CComponent
	{
		//Public Properties
	public:
		Framework::CGameObject *m_target;

	public:
		CameraController(Framework::CGameObject *game_object);
		~CameraController() = default;

	public:
		void Update(DWORD dt) override;
		void Render() override;

		void Following();
	};
}