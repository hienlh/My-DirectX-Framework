#include "DashFullEffect.h"
#include "Renderer.h"
#include "EffectPool.h"

void DashFullEffect::Update(const DWORD &dt)
{
	if (m_isDashing) {
		m_currentWaitTime += dt;
		if (m_currentWaitTime > m_waitForCreateSmoke)
		{
			EffectPool::GetInstance()->CreateEffect(Prefab_Effect_SmokeDash, m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position());
			m_currentWaitTime = 0;
		}
	}
}

void DashFullEffect::CreateDash() const
{
}

void DashFullEffect::CreateSmoke()
{
}

