#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Behavior.h"

namespace Framework
{
	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		CRenderer* m_rendererComponent = nullptr;
		CTransform* m_transformComponent = nullptr;
		CRigidbody* m_rigidbodyComponent = nullptr;
		std::vector<CComponent*> m_extendComponents;

		// Cons / Des
	public:
		CGameObject() = default;
		~CGameObject() = default;
		static bool leftBlockMoveDown;
		static bool rightBlockMoveDown;

		// Public methods
	public:
		bool AddComponent(SBuilder builder);
		bool AddComponent(EObjectType type);

		template<class T> bool AddComponent()
		{
			T* a = new T(this);
			if (reinterpret_cast<CComponent *> (&a)) {
				m_extendComponents.push_back(a);
			}
			return true;
		}
		template <> bool AddComponent<CRenderer>() { m_rendererComponent = new CRenderer(this); return true; }
		template <> bool AddComponent<CTransform>() { m_transformComponent = new CTransform(this); return true; }
		template <> bool AddComponent<CRigidbody>() { m_rigidbodyComponent = new CRigidbody(this); return true; }

		template<class Type>
		Type* GetComponent();

		bool RemoveComponent(EObjectType type);

		// Getters / Setters
	public:
		CTransform* GetTranform() const { return m_transformComponent; }
		CRigidbody* GetRigidbody() const { return m_rigidbodyComponent; }
		void AddRigidbody(CRigidbody* _rigidbody) { m_rigidbodyComponent = _rigidbody; }

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
