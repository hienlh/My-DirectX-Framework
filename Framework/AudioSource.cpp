#include "stdafx.h"
#include "Macros.h"
#include "AudioSource.h"
#include "ResourceManager.h"

using namespace Framework;

CAudioClip::CAudioClip(const CAudioClip& audioClip) : CObject(audioClip)
{
	m_pSound = audioClip.m_pSound;
	m_isLoop = audioClip.m_isLoop;
}

CAudioClip* CAudioClip::SetSound(const std::string& name)
{
	if (m_pSound)
		return nullptr;
	else
	{
		m_pSound = CResourceManager::GetInstance()->GetSound(name);
		return this;
	}
}

bool CAudioClip::Play() const
{
	bool result = false;

	do
	{
		CAudio* pAudio = CAudio::GetInstance();
		if (!pAudio)
			break;

		if (!m_pSound)
			break;

		if (!m_isLoop)
			pAudio->Play(m_pSound);
		else
			pAudio->PlayLoop(m_pSound);

		result = true;
	} while (false);

	return result;
}

bool CAudioClip::Stop() const
{
	bool result = false;

	do
	{
		CAudio* pAudio = CAudio::GetInstance();
		if (!pAudio)
			break;

		if (!m_pSound)
			break;

		pAudio->Stop(m_pSound);

		result = true;
	} while (false);

	return result;
}

/*
 * End of AudioClip
 */

CAudioSource::CAudioSource(const CAudioSource & audioSource) : CComponent(audioSource)
{
	m_pAudioClips = audioSource.m_pAudioClips;
}

CAudioSource& CAudioSource::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if(const auto pAudi = dynamic_cast<const CAudioSource*>(&component))
	{
		for (auto audio_clip : pAudi->m_pAudioClips)
		{
			if(m_pAudioClips.count(audio_clip.first))
			{
				*m_pAudioClips[audio_clip.first] = *audio_clip.second;
			}
		}
	}

	return *this;
}

CAudioSource * CAudioSource::Clone()
{
	return new CAudioSource(*this);
}

CAudioSource* CAudioSource::AddSound(CString name, bool isLoop)
{
	CAudioClip* pAudioClip = nullptr;
	bool result = false;
	do
	{
		if (m_pAudioClips.count(name))
			break;

		SAFE_ALLOC(pAudioClip, CAudioClip);
		pAudioClip->SetSound(name)->SetLoop(isLoop);

		m_pAudioClips.insert({ name, pAudioClip });

		result = true;
	} while (false);

	return (result ? this : nullptr);
}

bool CAudioSource::Play(CString name) const
{
	if (m_pAudioClips.count(name))
		return m_pAudioClips.at(name)->Play();
	else
		return false;
}

bool CAudioSource::Stop(CString name) const
{
	if (m_pAudioClips.count(name))
		return m_pAudioClips.at(name)->Stop();
	else
		return false;
}
