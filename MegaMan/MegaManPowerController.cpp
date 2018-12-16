#include "MegaManPowerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "BoxCollider.h"
#include "Input.h"
#include "Animator.h"
MegaManPowerController::MegaManPowerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

MegaManPowerController::~MegaManPowerController()
{
}
void MegaManPowerController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_E)) 
	{
		anim->SetBool("isPowering", true);
	}
	if (input->KeyUp(DIK_E)) 
	{
		anim->SetBool("isPowering", false);
		
		/*Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
		pos.x += 50;
		auto pBullet = CGameObject::Instantiate("BusterShot", nullptr, pos);
		pBullet->GetComponent<CRigidbody>()->SetVelocity({ .3,0 });*/
	}
	if(anim->GetBool("isPowering"))
	{
		transform->Set_Scale(Vector2(1, 1));
	}
	else
	{
		transform->Set_Scale(Vector2(0, 0));
	}
}

void MegaManPowerController::Render()
{
}
