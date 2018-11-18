#include "BallController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "BoxCollider.h"

BallController::BallController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

void BallController::OnCollisionEnter(CCollision* collision)
{
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(Vector2(0, -.1));
	m_pGameObject->GetScene()->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
}

void BallController::Update(DWORD dt)
{
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	Vector2 size = m_pGameObject->GetComponent<CBoxCollider>()->GetSize();
	
	if (pos.x + size.x >= SCREEN_WIDTH || pos.x < 0)
		transform->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
}

void BallController::Render()
{
}
