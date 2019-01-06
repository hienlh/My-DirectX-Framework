#include "BlastHornetController.h"
#include "GameObject.h"
#include "BlastHornetChildController.h"
#include "BlastHornetChild2Controller.h"
#include "BlastHornetBulletController.h"
#include "Renderer.h"

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

void BlastHornetController::OnTriggerEnter(CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	
		if (strstr(collisionName.c_str(), std::string("Wall").c_str()) || strstr(collisionName.c_str(), std::string("Ground").c_str()) || strstr(collisionName.c_str(), std::string("Ceiling").c_str())|| strstr(collisionName.c_str(), std::string("Door").c_str()))
		{
			isCollision = true;
		}

}

void BlastHornetController::Update(DWORD dt)
{
	Vector2 targetPos = m_target->GetComponent<CTransform>()->Get_Position();
	CTransform* transform = m_pGameObject->GetComponent<CTransform>();
	CRigidbody* rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CRenderer* renderer = m_pGameObject->GetComponent<CRenderer>();
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
		startFly += dt;
		transform->Set_Position(CalculatePosition(startFly, 1, 70));
	}

	//-----------------------------------
	//Flip controller
	//-----------------------------------
	if (myPos.x < targetPos.x - 5) renderer->SetFlipX(true);
	else if(myPos.x > targetPos.x + 5) renderer->SetFlipX(false);
	//-----------------------------------
	//Child Controller
	//-----------------------------------
	
		
		if (m_startBombing)
		{
			Bomb(myPos, targetPos);
			m_startBombing = false;
			
		} 
		else if(m_targeting)
		{
			Shoot(myPos, targetPos);
			m_targeting = false;
		}
		else if (m_attacking)
		{
			Attack(myPos, targetPos);
		}
		else
		{
			waitTime += dt;
			if (waitTime > 2000)
			{
				attackID = attackID > 10 ? 0 : (attackID+1);
				waitTime = 0;

				switch (attackID)
				{
				case 1:
				case 5:
					m_attacking = true;
					break;
				case 2:
				case 3:
				case 4:
					m_startBombing = true;
					break;
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					m_targeting = true;
					break;

				}
			}
			
		}
}

void BlastHornetController::Render()
{
}

void BlastHornetController::Shoot(Vector2 myPos, Vector2 targetPos)
{
	
	pBullet = CGameObject::Instantiate("BlastHornetBullet", nullptr, myPos);

	auto pChild1 = CGameObject::Instantiate("BlastHornetChild2", nullptr, myPos);
	auto pChild2 = CGameObject::Instantiate("BlastHornetChild2", nullptr, myPos);

	pChild1->GetComponent<BlastHornetChild2Controller>()->SetAliveTime(5000);
	pChild2->GetComponent<BlastHornetChild2Controller>()->SetAliveTime(5000);

	pChild1->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
	pChild2->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
}

void BlastHornetController::Bomb(Vector2 myPos, Vector2 targetPos)
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
	pChild2->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(15, 15), 0.2)));
	pChild3->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(00, 00), 0.2)));
	pChild4->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-15, -15), 0.2)));
	pChild5->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-30, -30), 0.2)));


	pChild1->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild2->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild3->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild4->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild5->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
}

void BlastHornetController::Attack(Vector2 myPos, Vector2 targetPos)
{
	CAnimator* animator = m_pGameObject->GetComponent<CAnimator>();
	CTransform* transform = m_pGameObject->GetComponent<CTransform>();
	CRigidbody* rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	if (m_startAttack == false)
	{
		m_lastPosition = transform->Get_Position();
		m_lastVelocity = rigidbody->GetVelocity();
		m_lastStartFly = startFly;
		animator->SetBool("isAttack", true);
		rigidbody->SetVelocity({ 0,0 });
		if (animator->GetCurrentAnimation()->IsLastFrame())
		{
			rigidbody->SetVelocity(CalculateVelocity(myPos, targetPos, 0.3));
			m_startAttack = true;
		}
	}
	else
	{
		
		if (isCollision)
		{
			rigidbody->SetVelocity(CalculateVelocity(myPos, m_lastPosition, 0.3));
			animator->SetBool("isAttack", false);
			isCollision = false;
		}
		Vector2 distance = Vector2(fabs(myPos.x - m_lastPosition.x), fabs(myPos.y - m_lastPosition.y));
		if(distance.x<10 && distance.y<10 && animator->GetBool("isAttack")==false)
		{
			m_attacking = false;
			m_startAttack = false;
			transform->Set_Position(m_lastPosition);
			rigidbody->SetVelocity(m_lastVelocity);
			startFly = m_lastStartFly;
		}
		
	}
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

Vector2 BlastHornetController::CalculatePosition(float dt, float velocity, float a)
{
	Rect limitedArea = m_pGameObject->GetComponent<CRigidbody>()->GetLimitedArea();
	Vector2 postion;
	postion.x = (a*sqrt(2)*cos(dt / 1000.0 * velocity)) / (pow(sin(dt / 1000.0 * velocity), 2)+1);
	postion.y = postion.x*sin(dt / 1000.0 * velocity);
	postion.x += (limitedArea.left + limitedArea.Size().x / 2);
	postion.y += (limitedArea.top + limitedArea.Size().y / 2);

	return postion;
}
