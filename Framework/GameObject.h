#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"
<<<<<<< HEAD
#include "Camera.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Scene.h"
=======
#include "Rigidbody.h"
#include "Animator.h"
>>>>>>> origin/dev

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
<<<<<<< HEAD
		String m_Name = String("");
		std::set<CComponent*> m_pComponents;
		CScene *m_pScene = nullptr; //Point to the scene which contain this gameObject;
=======
		//std::vector<CComponent*> m_components;
>>>>>>> origin/dev

		CRenderer* m_rendererComponent = nullptr;
		CTransform* m_transformComponent = nullptr;
		CRigidbody* m_rigidBodyComponent = nullptr;
		CAnimator* m_animatorComponent = nullptr;

		std::list<CComponent*> m_components{};
		
		// Cons / Des
	private:
		CGameObject() = default;
		~CGameObject() = default;

<<<<<<< HEAD
		// Friends
	public:
		friend class CScene;

		// Public methods
	public:
		/// <summary>Return nullptr if component added already</summary> 
		template<class T> T* AddComponent()
		{
			T* tmp = new T(this);
			if (reinterpret_cast<CComponent *> (&tmp)) {
				if (!m_pComponents.insert(tmp).second) return nullptr;
=======
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
>>>>>>> origin/dev

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
<<<<<<< HEAD
			for (CComponent* component : m_pComponents)
=======
			for (CComponent* component : m_components)
>>>>>>> origin/dev
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
<<<<<<< HEAD
			for (CComponent* component : m_pComponents)
=======
			for (CComponent* component : m_components)
>>>>>>> origin/dev
			{
				T* tmp = dynamic_cast<T *> (component);
				if (tmp != nullptr)
				{
					SAFE_DELETE(tmp);
				}
			}
			return true;
<<<<<<< HEAD
		}

		// Getters / Setters
	private:
		void SetScene(CScene *scene) { m_pScene = scene; }
	public:
		String GetName() const { return m_Name; }
=======
		}*/
>>>>>>> origin/dev

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
<<<<<<< HEAD
		static CGameObject* Instantiate();
		static CGameObject* Instantiate(String name, Vector2 position);
=======
		static CGameObject* Instantiate(Vector2 position = VECTOR2_ZERO);
>>>>>>> origin/dev
		static void Destroy(CGameObject* &instance);
	};
}
