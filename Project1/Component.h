#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Macros.h"
#include "Header.h"
#include "Object.h"

namespace Framework
{
	namespace Object
	{
		class CGameObject;

		// Component Class
		class CComponent : public Object::CObject
		{
		protected:
			CGameObject* _gameObject;

			// Cons / Des
		public:
			CComponent() = default;
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
			static CComponent* Instantiate(const Object::SBuilder &builder);
			static void Release(CComponent* &instance);
		};
	}
}
