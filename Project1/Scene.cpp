#include "Scene.h"
#include "Direct3DCore.h"
#include "GameManager.h"

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
	//int count = 0;
	//for (auto gameOnject : _listGameObject)
	//{
	//	gameOnject->Update(dt);

	//	switch (count)
	//	{
	//	case 0: //mario
	//	{
	//		float x = gameOnject->GetTranform()->position.x;
	//		float y = gameOnject->GetTranform()->position.y;
	//		float width = 14;
	//		float heigth = 27;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->position.y = SCREEN_HEIGHT - heigth;
	//		break;
	//	}
	//	case 1: //left block
	//	{
	//		float x = gameOnject->GetTranform()->position.x;
	//		float y = gameOnject->GetTranform()->position.y;
	//		float width = 10;
	//		float heigth = 150;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->position.y = SCREEN_HEIGHT - heigth;

	//		break;
	//	}
	//	case 2: //right block
	//	{
	//		float x = gameOnject->GetTranform()->position.x;
	//		float y = gameOnject->GetTranform()->position.y;
	//		float width = 10;
	//		float heigth = 150;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->position.y = SCREEN_HEIGHT - heigth;
	//		break;
	//	}
	//	}
	//	count = count >= 3 ? 0 : count + 1;
	//}
	for (auto gameOnject : _listGameObject)
	{
		gameOnject->Update(dt);
	}

	auto mario = _listGameObject[0];
		float mario_x = mario->GetTranform()->position.x;
		float mario_y = mario->GetTranform()->position.y;
		float mario_width = 14;
		float mario_heigth = 27;

	auto leftBlock = _listGameObject[1];
		float lblock_x = leftBlock->GetTranform()->position.x;
		float lblock_y = leftBlock->GetTranform()->position.y;
		float lblock_width = 10;
		float lblock_heigth = 150;
	auto rightBlock = _listGameObject[2];
		float rblock_x = rightBlock->GetTranform()->position.x;
		float rblock_y = rightBlock->GetTranform()->position.y;
		float rblock_width = 10;
		float rblock_heigth = 150;


	//Colission
	if (mario_x + mario_width >= SCREEN_WIDTH) mario->GetTranform()->position.x = SCREEN_WIDTH - mario_width;
	if (mario_y + mario_heigth >= SCREEN_HEIGHT) mario->GetTranform()->position.y = SCREEN_HEIGHT - mario_heigth;
	if (lblock_y + lblock_heigth >= SCREEN_HEIGHT) leftBlock->GetTranform()->position.y = SCREEN_HEIGHT - lblock_heigth;
	if (rblock_y + rblock_heigth >= SCREEN_HEIGHT) rightBlock->GetTranform()->position.y = SCREEN_HEIGHT - rblock_heigth;

	//va cham voi block trai
	if(mario_x + mario_width <= lblock_x + lblock_width && (mario_y + mario_heigth >= lblock_y && mario_y <= lblock_y +lblock_heigth))
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi block phai
	if(mario_x + mario_width>=rblock_x && (mario_y + mario_heigth >= rblock_y && mario_y <= rblock_y + rblock_heigth))
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi thanh duoi
	if (mario_y + mario_heigth>= SCREEN_HEIGHT)
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(velocity.x, -velocity.y));
	}

	//va cham voi thanh tren
	if (mario_y <= 0)
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(velocity.x, -velocity.y));
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