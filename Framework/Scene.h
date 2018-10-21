#pragma once
#include "Object.h"
#include "GameObject.h"

namespace Framework {
	class CScene : public CObject
	{
	private:
		std::vector<CGameObject*> _listGameObject;
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
		std::vector<CGameObject*> GetListGameObject();
		CGameObject* GetMainCamera() { return m_mainCamera; }

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt) override;
		void Render() override;

		void AddGameObject(CGameObject* gameObject);
	};
}
