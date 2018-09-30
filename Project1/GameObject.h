#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Object.h"

namespace Framework
{
	namespace Object
	{
		// Game Object Class
		class CGameObject : public CObject
		{
			// Properties
		private:
			Component::CRenderer* m_rendererComponent = nullptr;

			// Cons / Des
		public:
			CGameObject() = default;
			~CGameObject() = default;

			// Public methods
		public:
			bool AddComponent(EBuilderType componentType, Object::UBuilderData data);
			bool RemoveComponent(EBuilderType componentType);
			
			// Internal methods
		private:
			bool Init();
			void Destroy();

			// Override methods
		public:
			virtual void Update() override;

			// Static methods
		public:
			static CGameObject* Instantiate(const Object::SBuilder &builder);
			static void Release(CGameObject* &instance);
		};
	}
}
