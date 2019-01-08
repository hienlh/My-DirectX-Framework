#include "CarryAimController.h"
#include "CanBeAttacked.h"
#include "Macros.h"
#include "EffectPool.h"
#include "BuildingController.h"

using namespace Framework;

CarryAimController& CarryAimController::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	return *this;
}

void CarryAimController::Start()
{
	anim = m_pGameObject->GetComponent<CAnimator>();
	transform = m_pGameObject->GetComponent<CTransform>();
	parent = transform->GetParent()->GetGameObject();

	m_pBox = CGameObject::Instantiate(Prefab_Box, m_pGameObject, { 0,59 + 24 });
	m_pBox->GetComponent<CRigidbody>()->SetLimitedArea({ {4673, 930}, {256,350} });
}

void CarryAimController::Update(const DWORD& dt)
{
	if (const auto canBeAttacked = m_pGameObject->GetComponent<CanBeAttacked>()) 
	{
		if (canBeAttacked->GetCurrentHealth() <= 20 && !anim->GetBool(Bool_IsCollision)) 
		{
			auto pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
			pos.y += 30;
			EffectPool::GetInstance()->CreateEffect(
				Prefab_Effect_Explode, pos);
			anim->SetBool(Bool_IsCollision, true);
		}
	}

	if(m_moveIn)
	{
		const auto curPos = transform->GetLocalPosition();

		if (curPos.x - m_destination.x >= 0 && curPos.y - m_destination.y >= 0)
		{
			m_pBox->GetComponent<CTransform>()->SetParent(parent);
			parent->GetComponent<BuildingController>()->DeliverySuccess(m_pBox, m_destination);
			m_moveIn = false;
			MoveOut();
		}
		else {
			auto direction = m_destination - curPos;
			const auto min = min(direction.x, direction.y);
			if(min)
				direction = { direction.x / min, direction.y / min };
			transform->Translate(direction * 0.1 * dt);
		}
	}
	else if (m_moveOut)
	{
		const Vector2 destination = { 24, -110 };
		const auto curPos = transform->GetLocalPosition();

		if (fabs(curPos.x - destination.x) < 0.001 && fabs(curPos.y - destination.y) < 0.001)
		{
			m_moveOut = false;
			m_pGameObject->SetIsActive(false);
		}
		else {
			auto direction = destination - curPos;
			const auto min = min(fabs(direction.x), fabs(direction.y));
			if (min)
				direction = { direction.x / min, direction.y / min };
			transform->Translate(direction * 0.1 * dt);
		}
	}
}

void CarryAimController::MoveIn(const Vector2& destination)
{
	this->m_moveIn = true; 
	this->m_destination = destination;
}

bool CarryAimController::haveBox()
{
	return m_pBox->GetParent() == m_pGameObject || m_pBox->GetIsActive();
}
