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

void CAnimator::Update(DWORD dt)
{
	m_pCurrentAnimation->Update(dt);
}

void CAnimator::Render()
{
	Texture* pTexture = m_pCurrentAnimation->GetTexture();
	CTransform* pTransform = m_pGameObject->GetComponent<CTransform>();
	Rect rect = m_pCurrentAnimation->GetRect();
	CGraphic::GetInstance()->Draw(pTexture, &pTransform->Get_Position(), &rect, nullptr,
	                              pTransform->Get_Rotation().z);
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
