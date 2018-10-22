#pragma once
#include "Collider.h"

namespace Framework {

	class CCollision
	{
		// Properties
	private:
		CCollider *m_collider = nullptr;
		CCollider *m_otherCollider = nullptr;

		// Cons / Des
	public:
		CCollision(CCollider* collider, CCollider *otherCollider);
		CCollision(CGameObject* collider, CGameObject *otherCollider);
		~CCollision();

		//Getter / Setter
	public:
		CCollider *GetCollider() const { return m_collider; }
		CCollider *GetOtherCollider() const { return m_otherCollider; }

		Vector2 GetRelativeVelocity();
	};

}