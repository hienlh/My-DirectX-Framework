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
		// Component Class
		class CComponent : public Object::CObject
		{
			// Cons / Des
		public:
			CComponent() = default;
			virtual ~CComponent() = default;

			// Abstract Classes
		public:
			virtual void Update(DWORD dt);

			// Static methods
		public:
			static CComponent* Instantiate(const Object::SBuilder &builder);
			static void Release(CComponent* &instance);
		};
	}
}
