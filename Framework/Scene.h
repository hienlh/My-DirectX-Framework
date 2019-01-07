#pragma once
#include "Object.h"
#include "QuadTree.h"

namespace Framework
{
	class CGameObject;

	class CScene final : public CObject
	{
	private:
		std::set<CGameObject*> m_gameObjectList = {};
		std::set<CGameObject*> m_dynamicObjectList = {};
		std::set<CGameObject*> m_staticObjectList = {};
		std::set<CGameObject*> m_halfStaticObjectList = {};

		CQuadTree *m_pQuadTree = nullptr;
		CGameObject *m_pMainCamera = nullptr;
		bool m_loadedQuadTree = false;
		bool m_isRenderQuadTree = false;

	public:
		CScene(std::string name, Vector2 quadTreeSize = {1000, 1000});
		~CScene() = default;

	private:
		bool Init(std::string name, Vector2 quadTreeSize);
		bool InitMainCamera();
		bool Release();

		// Getter/Setter
	public:
		std::set<CGameObject*> GetListGameObject() const;
		std::set<CGameObject*> GetListDynamicGameObject() const;
		std::set<CGameObject*> GetActiveDynamicGameObject() const;
		std::set<CGameObject*> GetListStaticGameObject() const;
		std::set<CGameObject*> GetListHalfStaticGameObject() const;
		std::set<CGameObject*> GetActiveHalfStaticGameObject() const;
		std::set<CGameObject*> GetAllGameObjects() const;
		std::set<CGameObject*> GetRenderGameObjects() const;
		std::set<CGameObject*> GetUpdateGameObjects() const;
		CGameObject* GetMainCamera() const { return m_pMainCamera; }
		CQuadTree* GetQuadTree() const { return m_pQuadTree; }
		bool GetIsRenderQuadTree() const { return m_isRenderQuadTree; }

		CScene* SetIsRenderQuadTree(bool isRenderQuadTree) { m_isRenderQuadTree = isRenderQuadTree; return this; }

	public:
		static bool Destroy(CScene* scene);

		void Update(const DWORD &dt) override;
		void Render() override;

		//Internal Method
	private:
		void AddColliderObject(CGameObject* gameObject);

		//Method
	public:
		bool AddGameObject(Framework::CGameObject* gameObject);
		void RemoveGameObject(CGameObject* gameObject);
		CGameObject* FindGameObject(std::string name);
		CGameObject* FindGameObject(DWORD id);
		void SaveQuadTree() const;
		void LoadQuadTree() const;

		//Friend
	public:
		friend class CGameObject;
		friend class CRigidbody;
		friend class CBoxCollider;
		friend class CCollider;
		friend class CTransform;
	};
}
