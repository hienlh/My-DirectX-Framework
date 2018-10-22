#pragma once
#include "Object.h"

namespace Framework {
	class CGameObject;

	class CScene : public CObject
	{
	private:
		std::set<CGameObject*> m_listGameObject;
		std::set<CGameObject*> m_listColliderObject;
		CGameObject *m_mainCamera;

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
		CGameObject* GetMainCamera() const { return m_mainCamera; }

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt) override;
		void Render() override;

		void AddGameObject(CGameObject* gameObject);
		void AddGameObjects(int amount, CGameObject* gameObject, ...);

		//Internal Method
	private:
		void AddColliderObject(CGameObject* gameObject);

		//Friend
	public:
		friend class CGameObject;
	};
}
