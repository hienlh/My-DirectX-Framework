#pragma once
#include "Header.h"
#include "Component.h"

namespace Framework
{
	namespace Object {
		class CGameObject;
	}

	namespace Component
	{
		class CRenderer final : public Object::CComponent
		{
			// Properties
		private:
			Texture m_texture = nullptr;
			Object::CGameObject* m_parentObject = nullptr;

			// Cons / Des
		public:
			CRenderer() = default;
			virtual ~CRenderer() = default;

			// Internal methods
		private:
			bool Init(LPCSTR texturePath);
			void Release();

			// Static methods
		public:
			static CRenderer* Instantiate(Object::UObjectData data);
			static void Destroy(CRenderer* &instance);

			//Override method
		public:
			void Update(DWORD dt) override;
			void Render() override;
		};
	}
}
