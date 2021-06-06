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
		CGameObject(const bool& addIntoCurrentScene, const std::string &name, const Vector2 &position); //Just ResourceManager can use this function

	public:
		CGameObject(const CGameObject& gameObject);
		CGameObject(const std::string &name, const Vector2 &position = VECTOR2_ZERO) : CGameObject(true, name, position) {}
		~CGameObject();

		// Friends
	public:
		friend class CScene;
		friend class CPhysic;
		friend class CResourceManager;

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
		const DWORD& GetID() const { return m_id; }
		CGameObject* GetParent();
		Vector2 GetPosition();
		bool IsInCurrentScene() const;

		CGameObject* SetParent(CGameObject* parent);

		// Internal methods
	private:
		bool Init();
		void Release();
		void CheckAfterAddComponent(CComponent *component);
		bool AddComponent(CComponent *component);

		// Override methods
	public:
		void Update(const DWORD &dt) override;
		void Render() override;
		void CopyValue(const CGameObject& object);
		bool GetIsActive() override;

		CGameObject& operator=(const CGameObject& gameObject);

		// Static methods
	public:
		static CGameObject* Instantiate(CGameObject* gameObject, CGameObject* parent = nullptr,
		                                const Vector2 &position = VECTOR2_ZERO, const Vector3 &rotation = VECTOR3_ZERO,
		                                const bool &instantiateInWorldSpace = false);
		static CGameObject* Instantiate(const std::string &prefabName, CGameObject* parent = nullptr,
										const Vector2 &position = VECTOR2_ZERO, const Vector3 &rotation = VECTOR3_ZERO,
										const bool &instantiateInWorldSpace = false);
		static void Destroy(CGameObject* &instance);
	};
}
