#pragma once
#include "Object.h"

namespace Framework
{
	class CGameObject;

	// Component Class
	class CComponent : public CObject
	{
		// Cons / Des
	public:
		CComponent() = default;
		virtual ~CComponent() = default;

		//Getter / Setter
	public:
		//CGameObject* GetGameObject() { return _gameObject; }
		//void SetGameObject(CGameObject* gameobject) { m_gameObject = gameobject; }

		// Static methods
	public:
		static CComponent* Instantiate(SBuilder builder);
		static void Destroy(CComponent* &instance);
	};
}