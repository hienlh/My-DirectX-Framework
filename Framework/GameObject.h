#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "Scene.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

namespace Framework
{

	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
		static DWORD staticID;
	private:
		std::unordered_map<std::string, CComponent*> m_pComponents = {};
		CScene *m_pScene = nullptr;
		DWORD m_id = 0;
		
		// Cons / Des
	private:
		CGameObject() = default;
	public:
		CGameObject(const CGameObject& gameObject);
		CGameObject(std::string name, Vector2 position = VECTOR2_ZERO, bool addIntoCurrentScene = true);
		~CGameObject();

		// Friends
	public:
		friend class CScene;
		friend class CPhysic;

		// Public methods
	public:
		template<class T> bool CheckAddedComponent() const
		{
			return m_pComponents.count(typeid(T).name());
		}

		/// <summary>Return nullptr if component added already</summary> 
		template<class T> T* AddComponent()
		{
			std::string typeName = typeid(T).name();
			//Ignore Added Component and Base Component
			if(CheckAddedComponent<T>() || std::is_abstract<T>::value) return GetComponent<T>();
			
			T* tmp = new T(this);
			if (reinterpret_cast<CComponent *> (&tmp)) {
				if (!m_pComponents.insert({ typeName, tmp }).second) return nullptr;
				
				//if (reinterpret_cast<CCollider *> (&tmp) && m_pScene) //Da bi loi, sau khi co copy constructor
				if (typeName == typeid(CBoxCollider).name() && m_pScene)
				{
					if (!CheckAddedComponent<CRigidbody>())
						AddComponent<CRigidbody>();

					m_pScene->AddColliderObject(this);
				}

				CheckAfterAddComponent(tmp);

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

		/*template<class T>
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
		}*/

		// Getters / Setters
	private:
		void SetScene(CScene *scene) { m_pScene = scene; }
	public:
		CScene* GetScene() const { return m_pScene; }
		DWORD GetID() const { return m_id; }

		// Internal methods
	private:
		bool Init();
		void Release();
		void CheckAfterAddComponent(CComponent *component);
		bool AddComponent(CComponent *component);

		// Override methods
	public:
		void Update(DWORD dt) override;
		void Render() override;

		// Static methods
	public:
		static CGameObject* Instantiate(CGameObject* gameObject, CGameObject* parent = nullptr,
		                                Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO,
		                                bool instantiateInWorldSpace = false);
		static CGameObject* Instantiate(std::string prefabName, CGameObject* parent = nullptr,
										Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO,
										bool instantiateInWorldSpace = false);
		static void Destroy(CGameObject* &instance);
	};
}
