#pragma once
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

		public:
			virtual void Update() = 0;

			// Static methods
		public:
			static CComponent* Instantiate(SBuilder builder);
			static void Destroy(CComponent* &instance);
		};
	}
}
