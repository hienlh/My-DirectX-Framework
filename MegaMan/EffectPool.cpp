#include "EffectPool.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "GameManager.h"

EffectPool* EffectPool::__instance = nullptr;

void EffectPool::AddNewEffect(const std::string& prefabName)
{
	if (Framework::CGameManager::GetInstance()->IsRunning()) return;

	if(!m_pools.count(prefabName))
		if(const auto gameObject = Framework::CResourceManager::GetInstance()->GetPrefab(prefabName))
		{
			for (int i = 0; i < EFFECT_POOL_SIZE; ++i) {
				m_pools[prefabName][i] = new Framework::CGameObject(*gameObject);
				m_pools[prefabName][i]->SetIsActive(false);
			}
		}
}

Framework::CGameObject* EffectPool::CreateMultiEffect(const std::string& prefabName, const Rect& rect,
	const int& amount)
{
	for (int i = 0; i < amount; ++i)
	{
		const float x = rand() % static_cast<int>(rect.Size().x) + rect.left;
		const float y = rand() % static_cast<int>(rect.Size().y) + rect.top;
		CreateEffect(prefabName, Vector2(x, y));
	}

	return nullptr;
}

Framework::CGameObject* EffectPool::CreateEffect(const std::string& prefabName, const Vector2& position)
{
	if (!m_pools.count(prefabName)) return nullptr;

	for (int i = 0; i < EFFECT_POOL_SIZE; ++i)
	{
		if (!m_pools[prefabName][i]->GetIsActive())
		{
			*m_pools[prefabName][i] = *Framework::CResourceManager::GetInstance()->GetPrefab(prefabName);
			m_pools[prefabName][i]->SetIsActive(true);
			m_pools[prefabName][i]->GetComponent<Framework::CTransform>()->Set_Position(position);
			return m_pools[prefabName][i];
		}
	}

	return nullptr;
}

Framework::CGameObject* EffectPool::CreateMultiEffect(const std::string& prefabName, const Vector2& position,
                                                      const int& radius, const int& amount)
{
	for(int i = 0; i<amount; ++i)
	{
		const float x = rand() % (radius * 2) + (position.x - radius);
		const float y = rand() % (radius * 2) + (position.y - radius);
		CreateEffect(prefabName, Vector2(x,y));
	}

	return nullptr;
}
