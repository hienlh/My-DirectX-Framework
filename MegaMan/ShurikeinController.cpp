#include "ShurikeinController.h"
#include <GameObject.h>

ShurikeinController::ShurikeinController(CGameObject * gameObject) : CMonoBehavior(gameObject)
{
	
}


ShurikeinController::~ShurikeinController()
{
}

void ShurikeinController::OnTriggerEnter(CCollision * collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (strstr(collisionName.c_str(), "BusterShot"))
	{
		m_pGameObject->GetComponent<CAnimator>()->SetBool("isWasHit",true);
	}
}

void ShurikeinController::Update(DWORD dt)
{
	m_starttime += dt;
	
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
	if (m_starttime > 5000)
	{
		if (shuPos.y >= rectlimit.bottom && shuPos.x > rectlimit.left)
		{
			transform->Set_Position(Vector2(shuPos.x, rectlimit.bottom));
			rigidbody->SetVelocity({ -0.1,0 });
		}
		if (shuPos.x <= rectlimit.left && shuPos.y > rectlimit.top)
		{
			rigidbody->SetVelocity({ 0,-0.1 });
			transform->Set_Position(Vector2(rectlimit.left, shuPos.y));
		}
		if (shuPos.y <= rectlimit.top && shuPos.x < rectlimit.right)
		{
			rigidbody->SetVelocity({ 0.1,0 });
			transform->Set_Position(Vector2(shuPos.x, rectlimit.top));
		}
		if(shuPos.x >= rectlimit.right && shuPos.y < rectlimit.bottom)
		{
			rigidbody->SetVelocity({ 0,0.1 });
			transform->Set_Position(Vector2(rectlimit.right, shuPos.y));
		}
	}
	
}

void ShurikeinController::Render()
{
}
