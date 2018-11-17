#include "BallController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "BoxCollider.h"

BallController::BallController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void BallController::OnCollisionEnter(CCollision* collision)
{
	OutputDebugStringA("ab");
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(Vector2(0,.1));
	//m_pGameObject->GetScene()->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
}

void BallController::Update(DWORD dt)
{
}

void BallController::Render()
{
}
