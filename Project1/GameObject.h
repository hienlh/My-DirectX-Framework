#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"

namespace Framework
{
	namespace Object
	{
		// Game Object Class
		class CGameObject : public CObject
		{
			// Properties
		private:
			std::vector<CComponent*> m_components;

			Component::CRenderer* m_rendererComponent = nullptr;
			Component::CTransform* m_transformComponent = nullptr;

			// Cons / Des
		public:
			CGameObject() = default;
			~CGameObject() = default;

			// Public methods
		public:
			bool AddComponent(SBuilder builder);
			bool RemoveComponent(EObjectType type);

			// Getters / Setters
		public:
			Component::CTransform* Get_Transform() { return m_transformComponent; }
			
			void Update();

			// Internal methods
		private:
			bool Init();
			void Release();

			// Static methods
		public:
			static CGameObject* Instantiate();
			static void Destroy(CGameObject* &instance);
		};
	}
}
