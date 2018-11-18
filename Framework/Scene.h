#pragma once
#include "Object.h"

namespace Framework
{
	class CGameObject;

	class CScene final : public CObject
	{
	private:
		std::set<CGameObject*> m_gameObjectList = {};
		std::set<CGameObject*> m_colliderObjectList = {};
		CGameObject *m_pMainCamera = nullptr;

	public:
		CScene() = default;
		~CScene() = default;

	private:
		bool Init();
		bool InitMainCamera();
		bool Release();

		// Getter/Setter
	public:
		std::set<CGameObject*> GetListGameObject() const;
		std::set<CGameObject*> GetListColliderObject() const;
		CGameObject* GetMainCamera() const { return m_pMainCamera; }

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt);
		void Render();

		void AddGameObject(Framework::CGameObject* gameObject);
		void AddGameObjects(int amount, CGameObject* gameObject, ...);

		//Internal Method
	private:
		void AddColliderObject(CGameObject* gameObject);

		//Friend
	public:
		friend class CGameObject;
	};
}