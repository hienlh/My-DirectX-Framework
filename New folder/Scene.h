#pragma once
#include "Object.h"
#include "GameObject.h"
#include <vector>

class CScene : public Framework::Object::CObject
{
private:
	std::vector<Framework::Object::CGameObject*> _listGameObject;

public:
	CScene() = default;
	~CScene() = default;

private:
	bool Init();
	bool Release();

// Getter/Setter
public:
	std::vector<Framework::Object::CGameObject*> GetListGameObject();

public:
	static CScene* Instantiate();
	static bool Destroy(CScene* scene);

	void Update(DWORD dt) override;
	void Render();

	void AddGameObject(Framework::Object::CGameObject* gameObject);
};
