#pragma once
#include "Collider.h"
#include "GameObject.h"

namespace Framework {

	class CCollision
	{
		// Properties
	private:
		CCollider *m_pCollider = nullptr;
		CCollider *m_pOtherCollider = nullptr;

		// Cons / Des
	public:
		CCollision(CCollider* collider, CCollider *otherCollider);
		CCollision(CGameObject* collider, CGameObject *otherCollider);
		~CCollision();

		//Getter / Setter
	public:
		CCollider *GetCollider() const { return m_pCollider; }
		CCollider *GetOtherCollider() const { return m_pOtherCollider; }

		std::string GetColliderName() const { return m_pCollider->GetGameObject()->GetName(); }
		std::string GetOtherColliderName() const { return m_pOtherCollider->GetGameObject()->GetName(); }

		bool CollisionBetween(std::string name, std::string otherName) const;
	};

}
