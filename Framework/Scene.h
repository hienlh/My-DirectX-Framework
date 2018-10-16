#pragma once
#include "Object.h"
#include "GameObject.h"

namespace Framework {
	class CScene : public CObject
	{
	private:
		std::vector<CGameObject*> _listGameObject;

	public:
		CScene() = default;
		~CScene() = default;

	private:
		bool Init();
		bool Release();

		// Getter/Setter
	public:
		std::vector<CGameObject*> GetListGameObject();

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt) override;
		void Render() override;

		void AddGameObject(CGameObject* gameObject);
	};
}