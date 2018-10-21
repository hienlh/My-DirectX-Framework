#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Behavior.h"
#include "Camera.h"
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
		CRigidbody* m_rigidbodyComponent = nullptr;
		CAnimator* m_animatorComponent = nullptr;

		// Cons / Des
	private:
		CGameObject() = default;
		~CGameObject() = default;

	public:
		static bool leftBlockMoveDown;
		static bool rightBlockMoveDown;

		// Public methods
	public:
		template<class T> T* AddComponent()
		{
			if (GetComponent<T>()) return nullptr;
			T* tmp = new T(this);
			if (reinterpret_cast<CComponent *> (&tmp)) {
				m_Components.push_back(tmp);
				return tmp;
			}
			return nullptr;
		}

		template<class Type>
		Type* GetComponent()
		{
			for (CComponent* component : m_Components)
			{
				Type* tmp = dynamic_cast<Type *> (component);
				if(tmp != nullptr)
				{
					return tmp;
				}
			}
			return nullptr;
		}

		template<class T>
		bool RemoveComponent()
		{
			for (CComponent* component : m_Components)
			{
				T* tmp = dynamic_cast<T *> (component);
				if (tmp != nullptr)
				{
					SAFE_DELETE(tmp);
				}
			}
		}

		// Getters / Setters
	public:

		// Internal methods
	private:
		bool Init();
		void Release();

		// Override methods
	public:
		void Update(DWORD dt) override;
		void Render() override;

		// Static methods
	public:
		static CGameObject* Instantiate(Vector2 position = VECTOR2_ZERO);
		static void Destroy(CGameObject* &instance);
	};
}
