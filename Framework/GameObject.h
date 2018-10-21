#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Behavior.h"
#include "Camera.h"

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		std::vector<CComponent*> m_Components;

		// Cons / Des
	public:
		CGameObject() = default;
		~CGameObject() = default;
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
		static CGameObject* Instantiate();
		static CGameObject* Instantiate(Vector2 position);
		static void Destroy(CGameObject* &instance);
	};
}
