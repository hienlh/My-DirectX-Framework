#include "BuildingController.h"
#include "Renderer.h"
#include "Macros.h"
#include "CarryAimController.h"
#include "PlayerController.h"
#include "ResourceManager.h"
#include "MetaCapsuleController.h"

using namespace Framework;

void BuildingController::Start()
{
	m_pOutrigger = new CGameObject("Outrigger");
	m_pOutrigger->GetComponent<CTransform>()->SetParent(this->m_pGameObject)->Set_Position({ 112,0 }, false);
	m_pOutrigger->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 1)->SetZOrder(1)->GetSprite()->SetAnchor({0,0});

	for (int i = 0; i < CARRY_AIM_LIST_SIZE; ++i)
	{
		m_pCarryArmList[i] = CGameObject::Instantiate(Prefab_Carry_Aim, m_pGameObject, {24, -110});//{ 4691, 900 });
		m_pCarryArmList[i]->GetComponent<CRigidbody>()->SetLimitedArea({ {4673, 900}, {256,350} });
	}

	transform = m_pGameObject->GetComponent<CTransform>();

	m_pMetaCapsulePrefab = CResourceManager::GetInstance()->GetPrefab(Prefab_MetaCapsule);
	m_pMetaCapsulePrefab->GetComponent<MetaCapsuleController>()->player = player;
	m_pMetaCapsule = CGameObject::Instantiate(m_pMetaCapsulePrefab, m_pGameObject, { 96,64 });
}

void BuildingController::Update(const DWORD& dt)
{
	if(m_isTurnOn)
	{
		if(transform->Get_Position().y < 1023)
			transform->Translate(Vector2(0, 0.05)*dt);
		else
		{
			auto outriggerTransform = m_pOutrigger->GetComponent<CTransform>();
			if (outriggerTransform->Get_Position().y < transform->Get_Position().y + 88)
			{
				outriggerTransform->Translate(Vector2(0, 0.05)*dt);
			}
			else { //Complete TurnOn
				m_isTurnOn = false;
				TurnOnSpawn();
			}
		}
	}
	else if(m_isTurnOff)
	{
		auto outriggerTransform = m_pOutrigger->GetComponent<CTransform>();
		if (outriggerTransform->Get_Position().y >= transform->Get_Position().y)
		{
			outriggerTransform->Translate(Vector2(0, -0.05)*dt);
		}
		else
		{

			if (transform->Get_Position().y >= 1024 - 88) {
				transform->Translate(Vector2(0, -0.05)*dt);
			}
			else {
				m_isTurnOff = false;
				player->GetComponent<PlayerController>()->PassBuilding();
				m_pGameObject->SetIsActive(false);
			}
		}
	}
	else if(m_isSpawning)
	{
		if (m_turn < 10) {
			waitSpawnTime -= dt;
			if (waitSpawnTime <= 0)
			{
				Vector2 destination;
				if (FindDestination(destination))
				{
					m_pCarryArmList[m_turn]->SetIsActive(true);
					m_pCarryArmList[m_turn]->GetComponent<CarryAimController>()->MoveIn(destination);
					waitSpawnTime = TIME_WAIT_FOR_SPAWN;
					m_turn++;
				}
			}
		}
		else if (!m_pCarryArmList[9]->GetComponent<CarryAimController>()->haveBox() && !m_collectBoxes[0] && !m_collectBoxes[1])
		{
			TurnOff();
		}

		if (m_canFire && !m_pMetaCapsule->GetIsActive()) {
			if (waitFireTime > 0) waitFireTime -= dt;
			else
			{
				m_pMetaCapsule->SetIsActive(true);
				waitFireTime = TIME_WAIT_FOR_FIRE;
			}
		}
	}
}

void BuildingController::TurnOn()
{
	m_isTurnOn = true;
}

void BuildingController::TurnOff()
{
	m_isTurnOff = true;
}

void BuildingController::TurnOnSpawn()
{
	m_isSpawning = true;
}

void BuildingController::BoxIsDestroy(CGameObject* box)
{
	if (m_collectBoxes[0] == box)
		m_collectBoxes[0] = nullptr;
	else if(m_collectBoxes[1] == box)
		m_collectBoxes[1] = nullptr;

	m_canFire = false;
}

void BuildingController::DeliverySuccess(Framework::CGameObject* box, const Vector2& destination)
{
	if (m_cBoxDestination[0] == destination)
		m_collectBoxes[0] = box;
	else if (m_cBoxDestination[1] == destination)
		m_collectBoxes[1] = box;

	if (m_collectBoxes[0] && m_collectBoxes[1])
		m_canFire = true;
}

bool BuildingController::FindDestination(Vector2& destination)
{
	if (!m_collectBoxes[0]) {
		destination = m_cBoxDestination[0];
		return true;
	}
	
	if (!m_collectBoxes[1]) {
		destination = m_cBoxDestination[1];
		return true;
	}

	return false;
}


