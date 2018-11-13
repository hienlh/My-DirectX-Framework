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

bool CAnimator::Set(LPCWSTR texturePath, DWORD countWidth, DWORD countHeight, DWORD count, DWORD delay)
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

void CAnimator::Render()
{
	CTransform* pTransform = m_pGameObject->GetComponent<CTransform>();
	
	Rect rect;
	rect.left = (m_currentAnimation % m_animationCountWidth) * m_animationWidth;
	rect.top = (m_currentAnimation / m_animationCountWidth) * m_animationHeight;
	rect.right = rect.left + m_animationWidth;
	rect.bottom = rect.top + m_animationHeight;

	Vector2 center = Vector2(rect.left + m_animationWidth / 2, rect.top + m_animationHeight / 2);

	CGraphic::GetInstance()->Draw(m_pTexture, &pTransform->Get_Position(), &rect, nullptr, pTransform->Get_Rotation().z);
}

CAnimator* CAnimator::Instantiate()
{
	CAnimator* instance = nullptr;
	SAFE_ALLOC(instance, CAnimator);

	if (!instance->Init(L"", 0,0,0,0))
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
