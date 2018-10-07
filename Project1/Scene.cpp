#include "Scene.h"
#include "Direct3DCore.h"
#include <string>

bool CScene::Init()
{
	return true;
}

bool CScene::Release()
{
	bool result = false;
	do {
		for (auto gameObject : _listGameObject)
		{
			Framework::Object::CGameObject::Release(gameObject);
		}

		result = true;
	} while (false);

	return result;
}

std::vector<Framework::Object::CGameObject*> CScene::GetListGameObject()
{
	return _listGameObject;
}

CScene* CScene::Instantiate()
{
	CScene* scene = nullptr;
	SAFE_ALLOC(scene, CScene);

	if (!scene->Init())
		SAFE_DELETE(scene);

	return scene;
}

bool CScene::Destroy(CScene* scene)
{
	auto result = scene->Release();
	SAFE_DELETE(scene);

	return result;
}

void CScene::Update(DWORD dt)
{
	for (auto gameOnject : _listGameObject)
	{
		gameOnject->Update(dt);


		float x = gameOnject->GetTranform()->position.x;
		float y = gameOnject->GetTranform()->position.y;
		float width = 14;
		float heigth = 27;
		if (x + width <= SCREEN_WIDTH)
		{
			gameOnject->GetTranform()->position.x +=  0;

		}else gameOnject->GetTranform()->position.x = SCREEN_WIDTH;
		if (y + heigth <= SCREEN_HEIGHT)
		{
			gameOnject->GetTranform()->position.y += 10;

		}
		else gameOnject->GetTranform()->position.y = SCREEN_HEIGHT;

		// else if (y < SCREEN_HEIGHT -heigth && x >= SCREEN_WIDTH -width )
		// {
		// 	gameOnject->GetTranform()->position.y += dt / 10;
		// }
		// else if (x > 0 && y >= SCREEN_HEIGHT -heigth)
		// 	gameOnject->GetTranform()->position.x -= dt / 10;
		// else
		// 	gameOnject->GetTranform()->position.y -= dt / 10;
	}
}

void CScene::Render()
{
	Framework::Base::IDirect3DCore::GetInstance()->Render(_listGameObject);
}

void CScene::AddGameObject(Framework::Object::CGameObject* gameObject)
{
	_listGameObject.push_back(gameObject);
}