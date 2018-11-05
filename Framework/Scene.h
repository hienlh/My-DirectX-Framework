#pragma once
#include "Object.h"

<<<<<<< HEAD
namespace Framework {
	class CGameObject;

	class CScene : public CObject
	{
	private:
		std::set<CGameObject*> m_listGameObject;
		std::set<CGameObject*> m_listColliderObject;
		CGameObject *m_mainCamera;
=======
namespace Framework
{
	class CScene final : public CObject
	{
	private:
		std::list<Framework::CGameObject*> m_gameObjectList{};
>>>>>>> origin/dev

	public:
		CScene() = default;
		~CScene() = default;

	private:
		bool Init();
		bool Release();

		// Getter/Setter
	public:
<<<<<<< HEAD
		std::set<CGameObject*> GetListGameObject() const;
		std::set<CGameObject*> GetListColliderObject() const;
		CGameObject* GetMainCamera() const { return m_mainCamera; }
=======
		const std::list<Framework::CGameObject*>& GetGameObjectList();
>>>>>>> origin/dev

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt);
		void Render();

<<<<<<< HEAD
		void AddGameObject(CGameObject* gameObject);
		void AddGameObjects(int amount, CGameObject* gameObject, ...);

		//Internal Method
	private:
		void AddColliderObject(CGameObject* gameObject);

		//Friend
	public:
		friend class CGameObject;
=======
		void AddGameObject(Framework::CGameObject* gameObject);
>>>>>>> origin/dev
	};
}