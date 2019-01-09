#include "BlastHornetController.h"
#include "GameObject.h"
#include "BlastHornetChildController.h"
#include "BlastHornetChild2Controller.h"
#include "Renderer.h"
#include "Animator.h"
#include "Macros.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"
#include "AudioSource.h"
#include "Macros.h"
#include "Macros.h"

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

void BlastHornetController::Start()
{
	transform = m_pGameObject->GetComponent<CTransform>();
	anim = m_pGameObject->GetComponent<CAnimator>();
	rigid = m_pGameObject->GetComponent<CRigidbody>();
	renderer = m_pGameObject->GetComponent<CRenderer>();
	collider = m_pGameObject->GetComponent<CBoxCollider>();
}

void BlastHornetController::OnTriggerEnter(CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();

	if (strstr(collisionName.c_str(), std::string("Wall").c_str()) || strstr(collisionName.c_str(), std::string("Ground").c_str()) || strstr(collisionName.c_str(), std::string("Ceiling").c_str()) || strstr(collisionName.c_str(), std::string("Door").c_str()))
	{
		anim->SetBool(Bool_IsTargeted, true);
		isCollision = true;
	}
	if(collision->GetOtherCollider()->GetComponent<CanAttacked>())
	{
		m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Boss_wasHit);
	}
}

void BlastHornetController::Update(const DWORD& dt)
{
	if(!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		EffectPool::GetInstance()->CreateMultiEffect(Prefab_Effect_Explode_Blue, m_pGameObject->GetPosition(), 20, 6);
		m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Boss_Died);
		waitTimeWhenDie -= dt;
		if (waitTimeWhenDie < 0)

			m_pGameObject->SetIsActive(false);

		return;
	}

	const Vector2 targetPos = m_target->GetPosition();

	const Vector2 myPos = transform->Get_Position();


	//-----------------------------------
	//Flying controller
	//-----------------------------------
	if (!m_attacking)
	{
		startFly += dt;
		transform->Set_Position(CalculatePosition(startFly, 2, 70));
	}

	//-----------------------------------
	//Flip controller
	//-----------------------------------
	if (myPos.x < targetPos.x - 5) renderer->SetFlipX(true);
	else if (myPos.x > targetPos.x + 5) renderer->SetFlipX(false);
	//-----------------------------------
	//Child Controller
	//-----------------------------------


	if (m_startBombing)
	{
		Bomb(myPos, targetPos);
		m_startBombing = false;
		anim->SetBool(Bool_IsShoot, false);
	}
	else if (m_targeting)
	{
		anim->SetBool(Bool_IsShoot, true);
		Shoot(myPos, targetPos);
		m_targeting = false;
	}
	else if (m_attacking)
	{
		Attack(myPos, targetPos);
		anim->SetBool(Bool_IsShoot, false);
	}
	else
	{
		waitTime += dt;
		if (waitTime > 2000)
		{
			attackID = attackID > 10 ? 0 : (attackID + 1);
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
			default: m_targeting = true;
			}
		}

	}
}

void BlastHornetController::Shoot(const Vector2 &myPos, const Vector2 &targetPos)
{
	//if (pBullet) pBullet->SetIsActive(false);
	pBullet = CGameObject::Instantiate(Prefab_BlastHornet_Bullet, nullptr, myPos);

	auto pChild1 = CGameObject::Instantiate(Prefab_BlastHornet_Child2, nullptr, myPos);
	auto pChild2 = CGameObject::Instantiate(Prefab_BlastHornet_Child2, nullptr, myPos);

	pChild1->GetComponent<BlastHornetChild2Controller>()->SetAliveTime(5000);
	pChild2->GetComponent<BlastHornetChild2Controller>()->SetAliveTime(5000);

	pChild1->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
	pChild2->GetComponent<BlastHornetChild2Controller>()->SetTarget(m_target);
}

void BlastHornetController::Bomb(const Vector2 &myPos, const Vector2 &targetPos) const
{
	Vector2 distance = targetPos - myPos;
	auto pChild1 = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, myPos);
	auto pChild2 = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, myPos);
	auto pChild3 = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, myPos);
	auto pChild4 = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, myPos);
	auto pChild5 = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, myPos);

	pChild1->GetComponent<CTransform>()->Set_Position(myPos);
	pChild2->GetComponent<CTransform>()->Set_Position(myPos);
	pChild3->GetComponent<CTransform>()->Set_Position(myPos);
	pChild4->GetComponent<CTransform>()->Set_Position(myPos);
	pChild5->GetComponent<CTransform>()->Set_Position(myPos);

	pChild1->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild2->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild3->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild4->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);
	pChild5->GetComponent<BlastHornetChildController>()->SetAliveTime((rand() % 1000) + 1000);

	if (distance.x*distance.y > 0)
	{
		pChild1->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(30, -30), 0.1)));
		pChild2->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(15, -15), 0.1)));
		pChild3->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(00, 00), 0.1)));
		pChild4->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-15, 15), 0.1)));
		pChild5->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-30, 30), 0.1)));
	}
	else
	{
		pChild1->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(30, 30), 0.1)));
		pChild2->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(15, 15), 0.1)));
		pChild3->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(00, 00), 0.1)));
		pChild4->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-15, -15), 0.1)));
		pChild5->GetComponent<CRigidbody>()->SetVelocity(Vector2(CalculateVelocity(myPos, targetPos + Vector2(-30, -30), 0.1)));
	}
}

void BlastHornetController::Attack(const Vector2 &myPos, const Vector2 &targetPos)
{
	if (!m_startAttack)
	{
		m_lastPosition = transform->Get_Position();
		m_lastVelocity = rigid->GetVelocity();
		m_lastStartFly = startFly;
		anim->SetBool(Bool_IsAttack, true);
		rigid->SetVelocity({ 0,0 });
		if (anim->GetCurrentAnimation()->IsLastFrame())
		{
			rigid->SetVelocity(CalculateVelocity(myPos, targetPos, 0.2));
			m_startAttack = true;
		}
	}
	else
	{

		if (isCollision)
		{
			rigid->SetVelocity(CalculateVelocity(myPos, m_lastPosition, 0.2));
			anim->SetBool(Bool_IsAttack, false);
			isCollision = false;
		}
		const Vector2 distance = Vector2(fabs(myPos.x - m_lastPosition.x), fabs(myPos.y - m_lastPosition.y));
		if (distance.x < 10 && distance.y < 10 && anim->GetBool(Bool_IsAttack) == false)
		{
			m_attacking = false;
			m_startAttack = false;
			transform->Set_Position(m_lastPosition);
			rigid->SetVelocity(m_lastVelocity);
			startFly = m_lastStartFly;
		}

	}
}

Vector2 BlastHornetController::CalculateVelocity(const Vector2 &myPos, const Vector2 &targetPos, const float &size) const
{
	const float ratio = sqrt(pow((targetPos.x - myPos.x) / size, 2.0) + pow((targetPos.y - myPos.y) / size, 2.0));
	return Vector2((targetPos.x - myPos.x) / ratio, (targetPos.y - myPos.y) / ratio);
}

void BlastHornetController::AddChild(CGameObject* child)
{
	child1Pool.push_back(child);
}

CGameObject* BlastHornetController::GetDeactivateChild()
{
	const int size = child1Pool.size();
	for (int i = 0; i < size; i++)
	{
		if (child1Pool.at(i)->GetIsActive() == false) return child1Pool.at(i);
	}
	return m_pGameObject;
}

Vector2 BlastHornetController::CalculatePosition(const float& dt, const float& velocity, const float& a) const
{
	Rect limitedArea = rigid->GetLimitedArea();

	Vector2 position;
	position.x = (a*sqrt(2)*cos(dt / 1000.0 * velocity)) / (pow(sin(dt / 1000.0 * velocity), 2) + 1);
	position.y = position.x*sin(dt / 1000.0 * velocity);
	position.x += (limitedArea.left + limitedArea.Size().x / 2);
	position.y += (limitedArea.top + limitedArea.Size().y / 2);

	return position;
}
