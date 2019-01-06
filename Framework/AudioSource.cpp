#include "stdafx.h"
#include "Macros.h"
#include "AudioSource.h"
#include "ResourceManager.h"

using namespace Framework;

CAudioClip::CAudioClip(const CAudioClip& audioClip)
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
	CAudio* pAudio = nullptr;
	bool result = false;

	do
	{
		pAudio = CAudio::GetInstance();
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
	CAudio* pAudio = nullptr;
	bool result = false;

	do
	{
		pAudio = CAudio::GetInstance();
		if (!pAudio)
			break;

		if (!m_pSound)
			break;

		pAudio->Stop(m_pSound);

		result = true;
	} while (false);

	return result;
}

void CAudioClip::Update(DWORD dt)
{
}

void CAudioClip::Render()
{
}

CAudioClip * CAudioClip::Clone() const
{
	return new CAudioClip(*this);
}

/*
 * End of AudioClip
 */

CAudioSource::CAudioSource(const CAudioSource & audioSource)
{
	m_pAudioClips = audioSource.m_pAudioClips;
}

void CAudioSource::Update(DWORD dt)
{
}

void CAudioSource::Render()
{
}

CAudioSource * CAudioSource::Clone() const
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
