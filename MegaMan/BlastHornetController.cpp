#include "BlastHornetController.h"
#include "GameObject.h"
Vector2 InitPos;

BlastHornetController::BlastHornetController(const BlastHornetController& PC) : CMonoBehavior(PC)
{

}

BlastHornetController* BlastHornetController::Clone() const
{
	return new BlastHornetController(*this);
}

BlastHornetController::BlastHornetController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
	InitPos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
}


BlastHornetController::~BlastHornetController()
{
}

void BlastHornetController::Update(DWORD dt)
{
	//Flying controller
	Vector2 targetPos = m_target->GetComponent<CTransform>()->Get_Position();
	CTransform* transform = m_pGameObject->GetComponent<CTransform>();
	CRigidbody* rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CRenderer* renderer = m_pGameObject->GetComponent<CRenderer>();

		if (targetPos.x -5 > transform->Get_Position().x)
		{
			rigidbody->SetVelocity(Vector2(m_FlySpeed.x, m_FlySpeed.y));
			renderer->SetFlipX(true);
			// CDebug::Log(transform->Get_Position().x);
		}
		else if (targetPos.x +5< transform->Get_Position().x)
		{
			rigidbody->SetVelocity(Vector2(-m_FlySpeed.x, -m_FlySpeed.y));
			renderer->SetFlipX(false);
			// CDebug::Log(transform->Get_Position().x);
			// CDebug::Log("\n");
		} else rigidbody->SetVelocity(Vector2(0, 0));
}

void BlastHornetController::Render()
{
}
