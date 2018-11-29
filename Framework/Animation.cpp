#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"

using namespace Framework;

CAnimation::CAnimation(CWString name, DWORD defaultTime)
{
	m_defaultTime = defaultTime;
	if (!CResourceManager::GetInstance()->AddAnimation(name, this))
		delete this;
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

void CAnimation::Add(CSprite* sprite, DWORD time)
{
	Add({ sprite, time });
}

bool CAnimation::Add(CWString spriteName, DWORD time)
{
	if(CSprite* sprite = CResourceManager::GetInstance()->GetSprite(spriteName))
	{
		Add({ sprite, time });
		return true;
	}
	return false;
}
