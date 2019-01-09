#pragma once
#include "MonoBehavier.h"

#define CARRY_AIM_LIST_SIZE 10
#define TIME_WAIT_FOR_SPAWN 2000
#define TIME_WAIT_FOR_FIRE 500
#define MAX_SPAWN 2

class BuildingController : public Framework::CMonoBehavior
{
public:
	Framework::CGameObject* player = nullptr;

private:
	Framework::CGameObject* m_pCarryArmList[CARRY_AIM_LIST_SIZE] = {};
	Framework::CGameObject* m_pOutrigger = nullptr;
	Framework::CGameObject* m_pMetaCapsule = nullptr;
	Framework::CGameObject* m_pMetaCapsulePrefab = nullptr;

	bool m_isTurnOn = false;
	bool m_TurnedOn = false;
	bool m_isTurnOff = false;
	bool m_isSpawning = false;
	bool m_canFire = false;
	int m_turn = 0;
	int m_countBoxDestroyed = 0;

	int waitSpawnTime = 0;
	int waitFireTime = TIME_WAIT_FOR_FIRE;
	int currentSpawn = 0;

	const Vector2 m_cBoxDestination[2] = { {142,53}, {214,53} };
	Framework::CGameObject* m_collectBoxes[2] = {};

	Framework::CTransform* transform = nullptr;

public:
	BuildingController(const CMonoBehavior& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit BuildingController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	BuildingController* Clone() override { return new BuildingController(*this); }
	void Start() override;
	void Update(const DWORD& dt) override;

	void TurnOn();
	bool CheckTurnedOn() const { return m_TurnedOn; }
	void TurnOff();
	void TurnOnSpawn();
	void BoxIsDestroy(Framework::CGameObject* box);
	void DeliverySuccess(Framework::CGameObject* box, const Vector2& destination);

private:
	bool FindDestination(Vector2& destination);
};
