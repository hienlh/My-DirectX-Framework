#pragma once
#include "Object.h"
#include "GameObject.h"

namespace Framework {
	class CScene final : public CObject
	{
	private:
		std::list<Framework::CGameObject*> m_gameObjectList{};
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
		const std::list<Framework::CGameObject*>& GetGameObjectList();
		CGameObject* GetMainCamera() { return m_mainCamera; }

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt) override;
		void Render() override;

		void AddGameObject(CGameObject* gameObject);
	};
}
