#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "Graphic.h"
#include "ResourceManager.h"

using namespace Framework;

bool CAnimator::Init()
{
	return true;
}

void CAnimator::Release()
{
}

void CAnimator::AddAnimation(LPCWSTR animationName)
{
	CAnimation* anim = CResourceManager::GetInstance()->GetAnimation(animationName);

	if (anim) {
		if (m_Animations.size() <= 0) m_pCurrentAnimation = anim;
		m_Animations[animationName] = anim;
	}
}

void CAnimator::SetCurrentAnimation(LPCWSTR animationName)
{
	if(m_Animations[animationName])
	{
		m_pCurrentAnimation = m_Animations[animationName];
	}
}

CAnimation* CAnimator::GetCurrentAnimation() const
{
	return m_pCurrentAnimation;
}

CSprite* CAnimator::GetCurrentSprite() const
{
	return m_pCurrentAnimation->GetSprite();
}

void CAnimator::Update(DWORD dt)
{
	m_pCurrentAnimation->Update(dt);
}

void CAnimator::Render()
{
	//if (!m_pCurrentAnimation) return;
	//CSprite* sprite = m_pCurrentAnimation->GetSprite();
	//CTransform* pTransform = m_pGameObject->GetComponent<CTransform>();
	//Vector3 position3D = Vector3(pTransform->Get_Position());
	//position3D.z = 0;

	//CGraphic::GetInstance()->Draw(sprite, &position3D);
}

CAnimator* CAnimator::Instantiate()
{
	CAnimator* instance = nullptr;
	SAFE_ALLOC(instance, CAnimator);

	if (!instance->Init())
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

void CAnimator::Destroy(CAnimator*& instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
