#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"
#include "Scene.h"
#include "Collider.h"

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		LPCWSTR m_Name = L"";
		std::unordered_set<CComponent*> m_pComponents = {};
		CScene *m_pScene = nullptr;
		
		// Cons / Des
	private:
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
			if(GetComponent<T>()) return nullptr;
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
		LPCWSTR GetName() const { return m_Name; }
		CScene* GetScene() const { return m_pScene; }

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
		static CGameObject* Instantiate();
		static CGameObject* Instantiate(LPCWSTR name, Vector2 position);
		static CGameObject* Instantiate(Vector2 position);
		static void Destroy(CGameObject* &instance);
	};
}
