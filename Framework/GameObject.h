#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Transform.h"
#include "Rigidbody.h"
#include <vector>

namespace Framework
{

	// Game Object Class
	class CGameObject : public CObject
	{
		// Properties
	private:
		std::vector<CComponent*> m_components;

		CRenderer* m_rendererComponent = nullptr;
		CTransform* m_transformComponent = nullptr;
		CRigidbody* m_rigidbodyComponent = nullptr;

		// Cons / Des
	public:
		CGameObject() = default;
		~CGameObject() = default;
		static bool leftBlockMoveDown;
		static bool rightBlockMoveDown;

		// Public methods
	public:
		bool AddComponent(SBuilder builder);
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
		virtual void Update(DWORD dt);
		void Render();

		// Static methods
	public:
		static CGameObject* Instantiate();
		static CGameObject* Instantiate(Vector2 position);
		static void Destroy(CGameObject* &instance);
	};
}