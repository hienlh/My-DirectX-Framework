#pragma once
#include "Collider.h"
#include "GameObject.h"

namespace Framework {

	class CCollision
	{
		// Properties
	private:
		CGameObject *m_pCollider = nullptr;
		CGameObject *m_pOtherCollider = nullptr;

		// Cons / Des
	public:
		CCollision(const CCollision& collision, const bool &swap = false);
		CCollision(CGameObject* collider, CGameObject *otherCollider);
		~CCollision();

		//Getter / Setter
	public:
		CGameObject *GetCollider() const { return m_pCollider; }
		CGameObject *GetOtherCollider() const { return m_pOtherCollider; }
		
		const bool& CheckNameInCollision(const std::string& colliderName) const;
		const bool& CollisionBetween(const std::string& name, const std::string& otherName) const;

	public:
		friend class CPhysic;

		//Internal
	private:
		CCollision* Swap();
	};

}
