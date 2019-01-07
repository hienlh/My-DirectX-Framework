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
		explicit CComponent(CGameObject *game_object) { m_pGameObject = game_object; }
		virtual ~CComponent() = default;

		virtual CComponent* Clone() = 0;
		virtual CComponent& operator=(const CComponent& component)
		{
			(*this).CObject::operator=(component); 
			return *this;
		}

		//Getter / Setter
	public:
		CGameObject* GetGameObject() const { return m_pGameObject; }

	private:
		/**
		 * \brief Function is limited access from outside, just can access from CGameObject
		 */
		void SetGameObject(CGameObject* gameObject) { m_pGameObject = gameObject; }

	public:
		virtual void Update(const DWORD& dt) override {};
		virtual void Render() override {};
		//Friend
		friend class CPhysic;
		friend class CGameObject;
	};
}