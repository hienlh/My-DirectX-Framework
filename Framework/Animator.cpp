#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "Graphic.h"

using namespace Framework;

bool CAnimator::Init(LPCWSTR texturePath, DWORD countWidth, DWORD countHeight, DWORD count, DWORD delay)
{
	bool result = false;
	do
	{
		m_pTexture = CGraphic::GetInstance()->CreateTexture(texturePath, m_textureWidth, m_textureHeight);
		if (!m_pTexture)
			break;

		m_animationCountWidth = countWidth;
		m_animationCountHeight = countHeight;

		m_animationWidth = m_textureWidth / countWidth;
		m_animationHeight = m_textureHeight / countHeight;

		m_currentAnimation = 0;
		m_countAnimation = count;

		m_currentDelay = 0;
		m_thresholdDelay = delay;

		result = true;
	} while (false);
	
	return result;
}

void CAnimator::Release()
{
	if (m_pTexture)
		m_pTexture->Release();
}

void CAnimator::Update(DWORD dt)
{
	m_currentDelay += dt;
	if (m_currentDelay >= m_thresholdDelay)
	{
		m_currentDelay = 0;

		m_currentAnimation++;
		if (m_currentAnimation >= m_countAnimation)
			m_currentAnimation = 0;
	}
}

void Framework::CAnimator::Render()
{
	CTransform* pTransform = reinterpret_cast<CGameObject*>(m_parentObject)->GetTranform();
	
	Rect rect;
	rect.left = (m_currentAnimation % m_animationCountWidth) * m_animationWidth;
	rect.top = (m_currentAnimation / m_animationCountWidth) * m_animationHeight;
	rect.right = rect.left + m_animationWidth;
	rect.bottom = rect.top + m_animationHeight;

	CGraphic::GetInstance()->Draw(m_pTexture, pTransform->Get_Position(), &rect);
}

CAnimator* CAnimator::Instantiate(UObjectData data)
{
	CAnimator* instance = nullptr;
	SAFE_ALLOC(instance, CAnimator);

	instance->m_type = EObjectType::ANIMATOR;

	if (!instance->Init(data.animatorBuilder.texturePath, data.animatorBuilder.countWidth, data.animatorBuilder.countHeight, data.animatorBuilder.count, data.animatorBuilder.delay))
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
