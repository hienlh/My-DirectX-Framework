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
		std::unordered_map<std::string, CComponent*> m_pComponents = {};
		CScene *m_pScene = nullptr;
		
		// Cons / Des
	private:
		CGameObject() = default;
	public:
		CGameObject(LPCWSTR name, Vector2 position = VECTOR2_ZERO, bool addIntoCurrentScene = true);
		~CGameObject() = default;

		// Friends
	public:
		friend class CScene;
		friend class CPhysic;

		// Public methods
	public:
		/// <summary>Return nullptr if component added already</summary> 
		template<class T> T* AddComponent()
		{
			//Ignore Added Component and Base Component
			if(GetComponent<T>() || std::is_abstract<T>::value) return nullptr;
			
			T* tmp = new T(this);
			if (reinterpret_cast<CComponent *> (&tmp)) {
				if (!m_pComponents.insert({typeid(T).name(), tmp }).second) return nullptr;

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
			//Case get Component from Base Component. Ex: CBoxCollider && CCollider
			if(std::is_abstract<Type>::value)
			{
				for (auto component : m_pComponents)
				{
					Type* tmp = dynamic_cast<Type *> (component.second);
					if (tmp != nullptr)
					{
						return tmp;
					}
				}
				return nullptr;
			}

			//Case get Normal Component
			std::string key = typeid(Type).name();
			auto it = m_pComponents.find(key);
			if (it != m_pComponents.end())
			{
				return dynamic_cast<Type *> (it->second);
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
		static void Destroy(CGameObject* &instance);
	};
}
