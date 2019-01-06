#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Audio.h"

namespace Framework
{
	class CAudioClip final : public CObject
	{
	public:
		CAudioClip() = default;
		~CAudioClip() = default; 
		CAudioClip(const CAudioClip& audioClip);
		
	private:
		CSound* m_pSound = nullptr;
		bool m_isLoop = false;

	public:
		CAudioClip* SetLoop(bool isLoop) { m_isLoop = isLoop; return this; }
		CAudioClip* SetSound(const std::string &name);

		bool Play() const;
		bool Stop() const;

	public:
		void Update(DWORD dt) override;
		void Render() override;

		CAudioClip* Clone() const override;
	};

	class CAudioSource final : public CComponent
	{
		// Properties
	private:
		std::map<std::string, CAudioClip*> m_pAudioClips;

		// Cons / Des
	public:
		CAudioSource() = default;
		CAudioSource(const CAudioSource& audioSource);
		CAudioSource(CGameObject* gameObject) : CComponent(gameObject) {}
		
	public:
		void Update(DWORD dt) override;
		void Render() override;

		CAudioSource* Clone() const override;

	public:
		CAudioSource* AddSound(CString name, bool isLoop);

		bool Play(CString name) const;
		bool Stop(CString name) const;

	};
}
