#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Scene.h"

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		String m_Name = String("");
		std::set<CComponent*> m_pComponents;
		CScene *m_pScene = nullptr; //Point to the scene which contain this gameObject;

		// Cons / Des
	public:
		CGameObject() = default;
		~CGameObject() = default;

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
			for (CComponent* component : m_pComponents)
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
			for (CComponent* component : m_pComponents)
			{
				T* tmp = dynamic_cast<T *> (component);
				if (tmp != nullptr)
				{
					SAFE_DELETE(tmp);
				}
			}
			return true;
		}

		// Getters / Setters
	private:
		void SetScene(CScene *scene) { m_pScene = scene; }
	public:
		String GetName() const { return m_Name; }

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
		static CGameObject* Instantiate(String name, Vector2 position);
		static void Destroy(CGameObject* &instance);
	};
}
