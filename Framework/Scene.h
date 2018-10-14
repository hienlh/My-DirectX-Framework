#pragma once
#include "Object.h"
#include "GameObject.h"
#include <vector>

namespace Framework
{
	class CScene : public CObject
	{
	private:
		std::list<Framework::CGameObject*> m_gameObjectList;

	public:
		CScene() = default;
		~CScene() = default;

	private:
		bool Init();
		bool Release();

		// Getter/Setter
	public:
		//std::list<Framework::CGameObject*> GetGameObjectList();

	public:
		static CScene* Instantiate();
		static bool Destroy(CScene* scene);

		void Update(DWORD dt);
		void Render();

		void AddGameObject(Framework::CGameObject* gameObject);
	};
}