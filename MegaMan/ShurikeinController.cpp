#include "ShurikeinController.h"
#include <GameObject.h>
#include <Renderer.h>
#include <ctime>
#include <cstdlib>
bool isHitWall = false;
bool isHitShot = false;
int iran = 0;
ShurikeinController::ShurikeinController(CGameObject * gameObject) : CMonoBehavior(gameObject)
{
	srand((int)time(NULL));
}

void ShurikeinController::OnTriggerEnter(CCollision * collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (strstr(collisionName.c_str(), "BusterShot"))
	{
		//m_pGameObject->GetComponent<CAnimator>()->SetBool("isWasHit",true);
		isHitShot = true;
	}
	if (strstr(collisionName.c_str(), "Ceiling"))
	{
		isHitWall = true;
	}
}

void ShurikeinController::Update(const DWORD &dt)
{
	m_startTime += dt;

	if (isHitShot)
	{
		if (m_waitForChangeColor > 100)
			if (auto renderer = m_pGameObject->GetComponent<CRenderer>()) {
				if (renderer->GetFillColor() == D3DCOLOR_XRGB(255, 0, 0)) {
					renderer->SetFillColor(D3DCOLOR_XRGB(0, 0, 255));
				}
				else
					renderer->SetFillColor(D3DCOLOR_XRGB(255, 0, 0));

				m_waitForChangeColor = 0;
			}
		m_waitForChangeColor += dt;
	}

	auto rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	auto transform = m_pGameObject->GetComponent<CTransform>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	rectlimit = rigidbody->GetLimitedArea();
	rectlimit.top += 20;
	rectlimit.left += 20;
	rectlimit.bottom += -20;
	rectlimit.right += -20;
	//CDebug::Log("%d %d %d %d \n", rectlimit.top, rectlimit.left, rectlimit.bottom, rectlimit.right);
	Vector2 shuPos = transform->Get_Position();

	if (m_startTime > 2500)
	{
		Vector2 settingPos = shuPos;
		if (shuPos.y >= rectlimit.bottom)
		{
			settingPos = Vector2(shuPos.x, rectlimit.bottom);
		}
		if (shuPos.x <= rectlimit.left)
		{
			settingPos = Vector2(rectlimit.left, shuPos.y);
		}
		if (shuPos.y <= rectlimit.top)
		{

			settingPos = Vector2(shuPos.x, rectlimit.top);
		}
		if (shuPos.x >= rectlimit.right)
		{

			settingPos = Vector2(rectlimit.right, shuPos.y);
		}
		transform->Set_Position(settingPos);
		shuPos = settingPos;
		if (shuPos.x <= rectlimit.left && shuPos.y >= rectlimit.bottom)
		{
			iran = rand() % 2;
			CDebug::Log("%d \n", iran);
		}
		//iran = 1;
		switch (iran)
		{
		case 0:
		{
			if (shuPos.y >= rectlimit.bottom && shuPos.x > rectlimit.left)
			{
				transform->Set_Position(Vector2(shuPos.x, rectlimit.bottom));
				rigidbody->SetVelocity({ -0.2,0 });
			}
			if (shuPos.x <= rectlimit.left && shuPos.y > rectlimit.top)
			{
				rigidbody->SetVelocity({ 0,-0.2 });
				transform->Set_Position(Vector2(rectlimit.left, shuPos.y));
			}
			if (shuPos.y <= rectlimit.top && shuPos.x < rectlimit.right)
			{
				rigidbody->SetVelocity({ 0.2,0 });
				transform->Set_Position(Vector2(shuPos.x, rectlimit.top));
			}
			if (shuPos.x >= rectlimit.right && shuPos.y < rectlimit.bottom)
			{
				rigidbody->SetVelocity({ 0,0.2 });
				transform->Set_Position(Vector2(rectlimit.right, shuPos.y));
			}
			break;
		}

		case 1:
		{
			Vector2 velocity = rigidbody->GetVelocity();
			if (isHitShot && !isHitWall) velocity.y = -0.1;
			else if (isHitShot && isHitWall)
			{
				velocity.y = 0.1;
				isHitWall = false;
				isHitShot = false;
				m_pGameObject->GetComponent<CRenderer>()->SetFillColor(D3DCOLOR_XRGB(0, 0, 255));
			}

			if (shuPos.x <= rectlimit.left) velocity.x = +0.2;
			else if (shuPos.x >= rectlimit.right || velocity == Vector2(0, 0)) velocity.x = -0.2;
			rigidbody->SetVelocity(velocity);
			break;
		}
		default: ;
			/*
		case 2:
		{
			//rigidbody->SetVelocity({ 0,0 });
			break;
		}*/
		}
	}




}