#include "BlastHornetChildController.h"
#include "Animator.h"


void BlastHornetChildController::OnTriggerEnter(CCollision * collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if(!strstr(collisionName.c_str(),"BlastHornetChild") && !strstr(collisionName.c_str(), "Blast Hornet"))
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

void BlastHornetChildController::Update(DWORD dt)
{
	auto anim = m_pGameObject->GetComponent<CAnimator>();
	if(isStart) 
		aliveTime -= dt;
	// if(strstr(m_pGameObject->GetName().c_str(), std::string("70").c_str())) 
	// 	CDebug::Log("%s - %d\n", m_pGameObject->GetName().c_str(), aliveTime);
	destroyTime -= dt;
	if (aliveTime <= 0) Explosive();
	if (destroyTime <= 0) Explosive();
	//delete
	if(anim->GetBool("wasHit") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		SAFE_DELETE(m_pGameObject);
		// m_pGameObject->SetIsActive(false);
	}
}

void BlastHornetChildController::Render()
{
}

void BlastHornetChildController::Explosive()
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool("wasHit", true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 })->SetGravityScale(0);
}
