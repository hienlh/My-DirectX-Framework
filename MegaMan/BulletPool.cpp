﻿#include "BulletPool.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Animator.h"

BulletPool* BulletPool::__instance = nullptr;

void BulletPool::AddNewTypeBullet(const std::string& prefabName)
{
	if (Framework::CGameManager::GetInstance()->IsRunning()) return;

	if (!m_pools.count(prefabName))
		if (const auto gameObject = Framework::CResourceManager::GetInstance()->GetPrefab(prefabName))
		{
			for (int i = 0; i < EFFECT_POOL_SIZE; ++i) {
				m_pools[prefabName][i] = new Framework::CGameObject(*gameObject);
				m_pools[prefabName][i]->SetIsActive(false);
			}
		}
}

Framework::CGameObject* BulletPool::CreateBullet(const std::string& prefabName, const Vector2& position)
{
	if (!m_pools.count(prefabName)) return nullptr;

	for (int i = 0; i < EFFECT_POOL_SIZE; ++i)
	{
		if (!m_pools[prefabName][i]->GetIsActive())
		{
			//reset object
			*m_pools[prefabName][i] = *Framework::CResourceManager::GetInstance()->GetPrefab(prefabName);

			m_pools[prefabName][i]->SetIsActive(true);
			m_pools[prefabName][i]->GetComponent<Framework::CTransform>()->Set_Position(position);
			return m_pools[prefabName][i];
		}
	}

	return nullptr;
}
