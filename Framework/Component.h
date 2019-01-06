#pragma once
#include "Object.h"

namespace Framework
{
	class CGameObject;

	// Component Class
	class CComponent : public CObject
	{
	protected:
		CGameObject* m_pGameObject = nullptr;

		// Cons / Des
	public:
		CComponent() = default;
		CComponent(const CComponent& component) : CObject(component) { };
		CComponent(CGameObject *game_object) { m_pGameObject = game_object; }
		virtual ~CComponent() = default;
		virtual CComponent* Clone() = 0;

		//Getter / Setter
	public:
		CGameObject* GetGameObject() const { return m_pGameObject; }

	private:
		/**
		 * \brief Function is limited access from outside, just can access from CGameObject
		 */
		void SetGameObject(CGameObject* gameObject) { m_pGameObject = gameObject; }

		//Friend
	public:
		friend class CPhysic;
		friend class CGameObject;
	};
}