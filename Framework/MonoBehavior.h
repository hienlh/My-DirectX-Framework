﻿#pragma once
#include "Component.h"
#include "PhysicObserver.h"
#include "Physic.h"

namespace Framework {
	class CMonoBehavior : public CComponent , public CPhysicObserver
	{
	public:
		CMonoBehavior(CGameObject* gameObject) : CComponent(gameObject) { CPhysic::GetInstance()->RegisterObserver(this); }
		virtual ~CMonoBehavior() = default;
	};
}