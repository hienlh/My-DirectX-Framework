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
		CComponent(CGameObject *game_object) { m_pGameObject = game_object; }
		virtual ~CComponent() = default;

		// Override
	public:
		CWString GetName() const override;
		//Getter / Setter
	public:
		CGameObject* GetGameObject() { return m_pGameObject; }
		void SetGameObject(CGameObject* gameobject) { m_pGameObject = gameobject; }

		//Friend
	public:
		friend class CPhysic;
	};
}