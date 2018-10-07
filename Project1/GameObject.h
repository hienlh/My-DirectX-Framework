#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"
#include "Rigidbody.h"

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
			Component::CTransform* m_tranformComponent = nullptr;
			CRigidbody* m_rigidbodyComponent = nullptr;

			// Cons / Des
		public:
			CGameObject() = default;
			~CGameObject() = default;

			// Public methods
		public:
			bool AddComponent(Object::EBuilderType componentType, UBuilderData data);
			Component::CTransform* GetTranform() { return m_tranformComponent; }
			CRigidbody* GetRigidbody() { return m_rigidbodyComponent; }
			void AddRigidbody(CRigidbody* _rigidbody) { m_rigidbodyComponent = _rigidbody; }
			bool RemoveComponent(Object::EBuilderType componentType);

			// Internal methods
		private:
			bool Init();
			void Destroy();

			// Override methods
		public:
			virtual void Update(DWORD dt) override;
			void Render() override;

			// Static methods
		public:
			static CGameObject* Instantiate(Object::SBuilder builder);
			static CGameObject* Instantiate(Vector2 position);
			static void Release(CGameObject* &instance);
		};
	}
}
