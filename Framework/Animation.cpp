#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"

using namespace Framework;

CAnimation::CAnimation(CWString name, CWString textureName, DWORD startSprite, DWORD count, DWORD defaultTime, bool loop)
{
	bool result = false;
	do {
		CResourceManager* pResourceManager = CResourceManager::GetInstance();

		//Add texture, default time and list index of rect
		m_defaultTime = defaultTime;
		m_loop = loop;
		m_Name = name;

		for (int i = startSprite; i < startSprite + count; i++)
		{
			m_frames.push_back({ pResourceManager->GetSprite(textureName, i), defaultTime});
		}

		//Add animation to resource manager
		if (!pResourceManager->AddAnimation(name, this))
			break;

		result = true;
	} while (false);

	if(!result) delete this;
}

void CAnimation::Update(DWORD dt)
{
	const DWORD delayTime = m_frames[m_frameIndex].m_delay == 0 ? m_defaultTime : m_frames[m_frameIndex].m_delay;

	if (m_timeElapse >= delayTime)
	{
		m_timeElapse = 0;
		if (++m_frameIndex >= m_frames.size())
		{
			if(m_loop)
				m_frameIndex = 0;
			else m_frameIndex--;
		}
	}
	m_timeElapse += dt;
}

CSprite* CAnimation::GetSprite()
{
	return m_frames[m_frameIndex].m_sprite;
}

bool CAnimation::IsLastFrame() const
{
	const DWORD delayTime = m_frames[m_frameIndex].m_delay == 0 ? m_defaultTime : m_frames[m_frameIndex].m_delay;
	return m_frameIndex == m_frames.size() - 1 && m_timeElapse >= delayTime;
}

CAnimation* CAnimation::SetIndexCurrentFrame(int index)
{
	m_frameIndex = index;
	return this;
}

CAnimation* CAnimation::Add(CWString textureName, DWORD indexSprite, DWORD position, DWORD time)
{
	Add(CResourceManager::GetInstance()->GetSprite(textureName, indexSprite), position, time);
	return this;
}

void CAnimation::Render()
{
}

CAnimation* CAnimation::Add(SFrame frame)
{
	m_frames.push_back(frame);
	return this;
}

//void CAnimation::Add(Rect rect, DWORD time)
//{
//	Add({ rect, time });
//}

CAnimation* CAnimation::Add(CSprite* sprite, DWORD position, DWORD time)
{
	time = time != 0 ? time : m_defaultTime;

	if (position == -1) Add({ sprite, time });
	else m_frames.insert(m_frames.begin() + position, 1, { sprite, time });

	return this;
}
