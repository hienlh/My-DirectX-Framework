#pragma once
#include "Object.h"

namespace Framework
{
	class CGameObject;
	// Component Class
	class CComponent : public CObject
	{
	protected:
		CGameObject* _gameObject = nullptr;

		// Cons / Des
	public:
		CComponent() = default;
		CComponent(CGameObject *game_object) { _gameObject = game_object; }
		virtual ~CComponent() = default;

		//Getter / Setter
	public:
		CGameObject* GetGameObject() { return _gameObject; }
		void SetGameObject(CGameObject* gameobject) { _gameObject = gameobject; }

		// Abstract Classes
	public:
		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;

		// Static methods
	public:
		static CComponent* Instantiate(SBuilder builder);
		static void Destroy(CComponent* &instance);
	};
}
