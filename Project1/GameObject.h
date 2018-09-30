#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Transform.h"

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
			Component::CTransform* m_tranformComponent = nullptr;

			// Cons / Des
		public:
			CGameObject() = default;
			~CGameObject() = default;

			// Public methods
		public:
			bool AddComponent(Component::EComponentType componentType, Component::UBuilderData data);
			Component::CTransform* GetTranform() { return m_tranformComponent; }
			bool RemoveComponent(Component::EComponentType componentType);

			// Internal methods
		private:
			bool Init();
			void Destroy();

			// Static methods
		public:
			static CGameObject* Instantiate();
			static void Release(CGameObject * pObject);

			void Update();
			void Render();
		};

		class CMario : public CGameObject
		{

		};
	}
}
