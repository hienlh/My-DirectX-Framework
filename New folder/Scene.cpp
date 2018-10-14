#include "Scene.h"
#include "Direct3DCore.h"
#include "GameManager.h"
#include <string>
#include "Input.h"

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
			Framework::Object::CGameObject::Destroy(gameObject);
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
	//		float x = gameOnject->GetTranform()->m_position.x;
	//		float y = gameOnject->GetTranform()->m_position.y;
	//		float width = 14;
	//		float heigth = 27;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->m_position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->m_position.y = SCREEN_HEIGHT - heigth;
	//		break;
	//	}
	//	case 1: //left block
	//	{
	//		float x = gameOnject->GetTranform()->m_position.x;
	//		float y = gameOnject->GetTranform()->m_position.y;
	//		float width = 10;
	//		float heigth = 150;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->m_position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->m_position.y = SCREEN_HEIGHT - heigth;

	//		break;
	//	}
	//	case 2: //right block
	//	{
	//		float x = gameOnject->GetTranform()->m_position.x;
	//		float y = gameOnject->GetTranform()->m_position.y;
	//		float width = 10;
	//		float heigth = 150;
	//		//Colission
	//		if (x + width >= SCREEN_WIDTH) gameOnject->GetTranform()->m_position.x = SCREEN_WIDTH - width;
	//		if (y + heigth >= SCREEN_HEIGHT) gameOnject->GetTranform()->m_position.y = SCREEN_HEIGHT - heigth;
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
	float mario_x = mario->GetTranform()->m_position.x;
	float mario_y = mario->GetTranform()->m_position.y;
	float mario_width = 14;
	float mario_heigth = 27;

	auto leftBlock = _listGameObject[1];
	float lblock_x = leftBlock->GetTranform()->m_position.x;
	float lblock_y = leftBlock->GetTranform()->m_position.y;
	float lblock_width = 10;
	float lblock_heigth = 150;

	auto rightBlock = _listGameObject[2];
	float rblock_x = rightBlock->GetTranform()->m_position.x;
	float rblock_y = rightBlock->GetTranform()->m_position.y;
	float rblock_width = 10;
	float rblock_heigth = 150;


	//Colission
	//if (mario_x + mario_width >= SCREEN_WIDTH) mario->GetTranform()->m_position.x = SCREEN_WIDTH - mario_width;
	if (mario_y + mario_heigth >= SCREEN_HEIGHT) mario->GetTranform()->m_position.y = SCREEN_HEIGHT - mario_heigth;

	if (lblock_y + lblock_heigth >= SCREEN_HEIGHT) {
		leftBlock->GetTranform()->m_position.y = SCREEN_HEIGHT - lblock_heigth;
		Framework::Object::CGameObject::leftBlockMoveDown = false;
	}
	else if (lblock_y <= 0)
	{
		leftBlock->GetTranform()->m_position.y = 0;
		Framework::Object::CGameObject::leftBlockMoveDown = true;
	}
	if (rblock_y + rblock_heigth >= SCREEN_HEIGHT) {
		rightBlock->GetTranform()->m_position.y = SCREEN_HEIGHT - rblock_heigth;
		Framework::Object::CGameObject::rightBlockMoveDown = false;
	}
	else if (rblock_y <= 0)
	{
		rightBlock->GetTranform()->m_position.y = 0;
		Framework::Object::CGameObject::rightBlockMoveDown = true;
	}

	//va cham voi block trai
	if (mario_x <= lblock_x + lblock_width && (mario_y + mario_heigth >= lblock_y && mario_y <= lblock_y + lblock_heigth))
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi block phai
	if (mario_x + mario_width >= rblock_x && (mario_y + mario_heigth >= rblock_y && mario_y <= rblock_y + rblock_heigth))
	{
		auto velocity = mario->GetRigidbody()->GetVelocity();
		mario->GetRigidbody()->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi thanh duoi
	if (mario_y + mario_heigth >= SCREEN_HEIGHT)
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

	//Out screen
	if (mario_x + mario_width <= 0 || mario_x >= SCREEN_WIDTH)
	{
		mario->GetTranform()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	}



	auto input = Framework::Base::CInput::GetInstance();
	for (unsigned short x = 0; x <= 256; x++)
	{
		if (input->KeyDown(x))
		{
			if (x == 65)
			{
				leftBlock->GetRigidbody()->SetVelocity(Vector2(0, 3) * (Framework::Object::CGameObject::leftBlockMoveDown ? 1 : -1));
			}
			if (x == 1)
				rightBlock->GetRigidbody()->SetVelocity(Vector2(0, 3) *(Framework::Object::CGameObject::rightBlockMoveDown ? 1 : -1));
		}
		if (input->KeyUp(x))
		{
			if (x == 65)
			{
				leftBlock->GetRigidbody()->SetVelocity(Vector2(0, 0));
			}
			if (x == 1)
				rightBlock->GetRigidbody()->SetVelocity(Vector2(0, 0));
		}
	}
}

void CScene::Render()
{
	Framework::Base::IGraphic::GetInstance()->Render(_listGameObject);
}

void CScene::AddGameObject(Framework::Object::CGameObject* gameObject)
{
	_listGameObject.push_back(gameObject);
}