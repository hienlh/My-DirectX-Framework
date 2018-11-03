#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		//std::vector<CComponent*> m_components;

		CRenderer* m_rendererComponent = nullptr;
		CTransform* m_transformComponent = nullptr;
		CRigidbody* m_rigidBodyComponent = nullptr;
		CAnimator* m_animatorComponent = nullptr;

		std::list<CComponent*> m_components{};
		
		// Cons / Des
	private:
		CGameObject() = default;
		~CGameObject() = default;

	public:
		static bool leftBlockMoveDown;
		static bool rightBlockMoveDown;

		// Public methods
	public:
		bool AddComponent(SBuilder builder);
		//bool RemoveComponent(EObjectType type);*/

		// Getters / Setters
	public:
		CTransform* GetTransform() const { return m_transformComponent; }
		CRigidbody* GetRigidBody() const { return m_rigidBodyComponent; }
		void AddRigidbody(CRigidbody* pRigidbody) { m_rigidBodyComponent = pRigidbody; }

	public:
		/*template<class T> T* AddComponent()
		{
			T* tmp = new T(this);
			if (reinterpret_cast<CComponent *> (&tmp)) {
				if (!m_components.insert(tmp).second) return nullptr;

				if (reinterpret_cast<CCollider *> (&tmp) && m_pScene)
				{
					m_pScene->AddColliderObject(this);
				}
				return tmp;
			}
			return nullptr;
		}

		template<class Type>
		Type* GetComponent()
		{
			for (CComponent* component : m_components)
			{
				Type* tmp = dynamic_cast<Type *> (component);
				if (tmp != nullptr)
				{
					return tmp;
				}
			}
			return nullptr;
		}

		template<class T>
		bool RemoveComponent()
		{
			for (CComponent* component : m_components)
			{
				T* tmp = dynamic_cast<T *> (component);
				if (tmp != nullptr)
				{
					SAFE_DELETE(tmp);
				}
			}
			return true;
		}*/

		// Internal methods
	private:
		bool Init();
		void Release();

		// Override methods
	public:
		virtual void Update(DWORD dt);
		void Render();

		// Static methods
	public:
		static CGameObject* Instantiate(Vector2 position = VECTOR2_ZERO);
		static void Destroy(CGameObject* &instance);
	};
}
