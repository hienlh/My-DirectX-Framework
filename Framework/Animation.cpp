#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"

using namespace Framework;

CAnimation::CAnimation(const CAnimation& animation) : CObject(animation)
{
	m_loop = animation.m_loop;
	m_defaultTime = animation.m_defaultTime;
	m_frames = animation.m_frames;
	m_frameIndex = 0;
	m_timeElapse = animation.m_timeElapse;
	m_Name = animation.m_Name;
	m_speed = animation.m_speed;
}

CAnimation::CAnimation(std::string name, std::string textureName, DWORD startSprite, DWORD count, DWORD defaultTime, bool loop, float speed)
{
	bool result = false;
	do {
		CResourceManager* pResourceManager = CResourceManager::GetInstance();

		//Add texture, default time and list index of rect
		m_defaultTime = defaultTime;
		m_loop = loop;
		m_Name = name;
		m_speed = speed;

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

void CAnimation::Update(const DWORD &dt)
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
	m_timeElapse += dt * fabs(m_speed);
}

CSprite* CAnimation::GetSprite()
{
	return m_frames[m_frameIndex].m_sprite;
}

const bool &CAnimation::IsLastFrame() const
{
	const DWORD delayTime = m_frames[m_frameIndex].m_delay == 0 ? m_defaultTime : m_frames[m_frameIndex].m_delay;
	return m_frameIndex == m_frames.size() - 1 && m_timeElapse >= delayTime;
}

CAnimation* CAnimation::Add(const std::string& textureName, const DWORD& indexSprite, const DWORD& pos,
	const DWORD& time)
{
	Add(CResourceManager::GetInstance()->GetSprite(textureName, indexSprite), pos, time);
	return this;
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

CAnimation* CAnimation::Add(CSprite* sprite, const DWORD& pos, const DWORD& time)
{
	const auto _time = time != 0 ? time : m_defaultTime;

	if (pos == -1) Add({ sprite, time });
	else m_frames.insert(m_frames.begin() + pos, 1, { sprite, _time });

	return this;
}
