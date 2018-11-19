#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"

using namespace Framework;

void CAnimation::Init(LPCWSTR textureName, DWORD defaultTime)
{
	m_pTexture = CResourceManager::GetInstance()->GetTexture(textureName);
	m_defaultTime = defaultTime;
}

void CAnimation::Update(DWORD dt)
{
	m_timeElapse += dt;
	const DWORD delayTime = m_frames[m_frameIndex].m_delay == 0 ? m_defaultTime : m_frames[m_frameIndex].m_delay;

	if (m_timeElapse >= delayTime)
	{
		m_timeElapse = 0;
		if (++m_frameIndex >= m_frames.size())
			m_frameIndex = 0;
	}
}

void CAnimation::Render()
{
}

void CAnimation::Add(SFrame frame)
{
	m_frames.push_back(frame);
}

void CAnimation::Add(Rect rect, DWORD time)
{
	Add({ rect, time });
}

CAnimation* CAnimation::Instantiate(LPCWSTR name, LPCWSTR textureName, DWORD defaultTime)
{
	CAnimation* anim = nullptr;
	SAFE_ALLOC(anim, CAnimation);

	anim->Init(textureName, defaultTime);

	CResourceManager::GetInstance()->AddAnimation(name, anim);

	return anim;
}
