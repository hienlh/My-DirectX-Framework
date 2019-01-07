#include "BlastHornetChildController.h"
#include "Animator.h"
#include "EffectPool.h"
#include "Macros.h"


void BlastHornetChildController::OnTriggerEnter(CCollision * collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (!strstr(collisionName.c_str(), "BlastHornetChild") && !strstr(collisionName.c_str(), "Blast Hornet"))
	{
		if (strstr(collisionName.c_str(), std::string("Wall").c_str()) || strstr(collisionName.c_str(), std::string("Ground").c_str()) || strstr(collisionName.c_str(), std::string("Ceiling").c_str()))
		{
			isStart = true;
			m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 })->SetGravityScale(0);
		}
		else
			Explosive();

	}
}

void BlastHornetChildController::Update(const DWORD& dt)
{
	if (isStart)
		aliveTime -= dt;

	destroyTime -= dt;

	if (aliveTime <= 0) Explosive();

	if (destroyTime <= 0) Explosive();
}

void BlastHornetChildController::Render()
{
}

void BlastHornetChildController::Explosive()
{
	EffectPool::GetInstance()->CreateEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition());
	m_pGameObject->SetIsActive(false);
}
