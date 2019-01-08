#include "EffectAutoRemove.h"
#include "Animator.h"

void EffectAutoRemove::Update(const DWORD &dt)
{
	if(auto anim = m_pGameObject->GetComponent<Framework::CAnimator>())
	{
		if(anim->GetCurrentAnimation()->IsLastFrame())
		{
			m_pGameObject->SetIsActive(false);
		}
	}
}
