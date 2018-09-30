#pragma once
#include "Component.h"
#include "Renderer.h"

namespace Framework
{
	namespace Object
	{
		// Game Object Class
		class CGameObject
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
			bool AddComponent(Component::EComponentType componentType, Component::UBuilderData data);
			bool RemoveComponent(Component::EComponentType componentType);
			
			// Internal methods
		private:
			bool Init();
			void Destroy();

			// Static methods
		public:
			static CGameObject* Instantiate();
			static void Release(CGameObject * pObject);
		};

		class CMario : public CGameObject
		{
			
		};
	}
}
