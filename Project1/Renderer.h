#pragma once
#include "Header.h"
#include "Component.h"

namespace Framework
{
	namespace Component
	{
		class CRenderer final : public Object::CComponent
		{
			// Properties
		private:
			Texture m_texture = nullptr;

			// Cons / Des
		public:
			CRenderer() = default;
			virtual ~CRenderer() = default;

			// Internal methods
		private:
			bool Init(LPCSTR texturePath);
			void Destroy();

			// Static methods
		public:
			static CRenderer* Instantiate(LPCSTR texturePath);
			static void Release(CRenderer* &pObject);

			void Update(Vector3 position);
			void Render() override;
		};
	}
}
