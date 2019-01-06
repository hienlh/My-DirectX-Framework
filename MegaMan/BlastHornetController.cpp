#include "BlastHornetController.h"
#include "GameObject.h"
#include "BlastHornetChildController.h"
#include "BlastHornetChild2Controller.h"
#include "BlastHornetBulletController.h"
#include "Renderer.h"
Vector2 InitPos;
DWORD waitTime=0;
int targetTime = 0;
CGameObject* pBullet=nullptr;

BlastHornetController::BlastHornetController(const BlastHornetController& PC) : CMonoBehavior(PC)
{

}

BlastHornetController* BlastHornetController::Clone() 
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
	Vector2 targetPos = m_target->GetComponent<CTransform>()->Get_Position();
	CTransform* transform = m_pGameObject->GetComponent<CTransform>();
	CRigidbody* rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CAnimator* animator = m_pGameObject->GetComponent<CAnimator>();
	Bound myBound = m_pGameObject->GetComponent<CCollider>()->GetBoundGlobal();
	Vector2 veclocity = rigidbody->GetVelocity();
	Vector2 myPos = transform->Get_Position();
	Vector2 temp;

	
	//-----------------------------------
	//Flying controller
	//-----------------------------------
	if (!m_attacking)
	{
		if (myBound.intersect(m_topRight))
		{
			veclocity = Vector2({ -m_flySpeed,0 });
		}
		else if (myBound.intersect(m_topLeft))
		{
			veclocity = Vector2({ 0,m_flySpeed });
		}
		else if (myBound.intersect(m_bottomLeft))
		{
			veclocity = Vector2({ m_flySpeed,0 });
		}
		else if (myBound.intersect(m_bottomRight))
		{
			veclocity = Vector2({ 0,-m_flySpeed });
		}
		rigidbody->SetVelocity(veclocity);
	}
	//-----------------------------------
	//Child Controller
	//-----------------------------------
	
		waitTime += dt;
		if (m_startBombing)
		{
			if (waitTime >= 2000)
			{
				
				auto pChild1 = CGameObject::Instantiate("BlastHornetChild", nullptr, myPos);
				auto pChild2 = CGameObject::Instantiate("BlastHornetChild", nullptr, myPos);
				auto pChild3 = CGameObject::Instantiate("BlastHornetChild", nullptr, myPos);
				auto pChild4 = CGameObject::Instantiate("BlastHornetChild", nullptr, myPos);
				auto pChild5 = CGameObject::Instantiate("BlastHornetChild", nullptr, myPos);
				// auto pChild1 = GetDisactiveChild(); pChild1->SetIsActive(true);
				// auto pChild2 = GetDisactiveChild();	pChild2->SetIsActive(true);
				// auto pChild3 = GetDisactiveChild();	pChild3->SetIsActive(true);
				// auto pChild4 = GetDisactiveChild();	pChild4->SetIsActive(true);
				// auto pChild5 = GetDisactiveChild();	pChild5->SetIsActive(true);
				
				pChild1->GetComponent<CTransform>()->Set_Position(myPos);
				pChild2->GetComponent<CTransform>()->Set_Position(myPos);
				pChild3->GetComponent<CTransform>()->Set_Position(myPos);
				pChild4->GetComponent<CTransform>()->Set_Position(myPos);
				pChild5->GetComponent<CTransform>()->Set_Position(myPos);

				pChild1->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(30, 30), 0.2)));
				pChild2->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(15,15), 0.2)));
				pChild3->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(00,00), 0.2)));
				pChild4->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-15,-15), 0.2)));
				pChild5->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-30,-30), 0.2)));
				
				
				pChild1->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
				pChild2->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
				pChild3->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
				pChild4->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
				pChild5->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);

				// m_startBombing = false;
				waitTime = 0;
				}
			
		} 
	else if(m_targeting)
		{
			targetTime += dt;
			if(targetTime >=7000)
			{
				pBullet = CGameObject::Instantiate("BlastHornetBullet", nullptr, myPos);
				targetTime = 0;
			}
			if(waitTime>2000)
			{
				if(m_isTargeted)
				{
					auto pChild1 = CGameObject::Instantiate("BlastHornetChild2", nullptr, myPos);
					pChild1->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
					auto pChild2 = CGameObject::Instantiate("BlastHornetChild2", nullptr, myPos);
					pChild2->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
				}
				
				waitTime = 0;
			}
			m_targeting = false;
			
		}
	else if (m_attacking)
		{
			
			if (animator->GetBool("isAttack") == false)
			{
				m_lastPosition = transform->Get_Position();
				m_lastVelocity = rigidbody->GetVelocity();
				animator->SetBool("isAttack", true);
				rigidbody->SetVelocity({ 0,0 });
			}
			else
			{
				if (animator->GetCurrentAnimation()->IsLastFrame())
				{
					rigidbody->SetVelocity(CalculateVelocity(myPos, targetPos, 0.3));
				}
				m_attacking = false;
			}
		}
}

void BlastHornetController::Render()
{
}

void BlastHornetController::Shoot(Vector2 targetPos)
{

}

Vector2 BlastHornetController::CalculateVelocity(Vector2 myPos, Vector2 targetPos, float size)
{
	float ratio = sqrt(pow((targetPos.x - myPos.x) / size, 2.0) + pow((targetPos.y - myPos.y) / size, 2.0));
	return Vector2((targetPos.x - myPos.x)/ratio,(targetPos.y - myPos.y)/ratio);
}

void BlastHornetController::AddChild(CGameObject* child)
{
	child1Pool.push_back(child);
}

CGameObject* BlastHornetController::GetDisactiveChild()
{
	int n = child1Pool.size();
	for (int i=0;i<n;i++)
	{
		if (child1Pool.at(i)->GetIsActive() == false) return child1Pool.at(i);
	}
}
