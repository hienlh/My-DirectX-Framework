#pragma once
#include "stdafx.h"
#include "Object.h"

namespace Framework {
	class CAnimation : public CObject
	{

	public:
		struct SFrame
		{
			CSprite *m_sprite;
			DWORD m_delay = 0;
		};

	private:
		std::vector<SFrame> m_frames = {};

		DWORD m_frameIndex = 0;
		DWORD m_timeElapse = 0;
		DWORD m_defaultTime = 0;
		bool m_loop = true;
		float m_speed = 1;

	private:
		CAnimation() = default;
	public:
		CAnimation(const CAnimation& animation);
		CAnimation(std::string name, std::string textureName, DWORD startSprite, DWORD count, DWORD defaultTime = 100, bool loop = true, float speed = 1);
		~CAnimation() = default;

	private:
		void Render() override {};
	public:
		void Update(const DWORD &dt) override;

		// Getter / Setter
	public:
		CSprite* GetSprite();
		const bool &IsLastFrame() const;
		const bool &GetIndexCurrentFrame() const { return m_frameIndex; }
		const DWORD &GetSpeed() const { return m_speed; }
		const std::vector<SFrame> &GetFrames() const { return m_frames; }

		CAnimation* SetIndexCurrentFrame(const int &index){	m_frameIndex = index; return this; }
		CAnimation* SetSpeed(const DWORD &speed) { m_speed = speed; return this; }

		//Method
	public:
		CAnimation* Add(const std::string& textureName, const DWORD& indexSprite, const DWORD& pos = -1,
		                const DWORD& time = 0);
		CAnimation* Add(CSprite* sprite, const DWORD &pos = -1, const DWORD &time = 0);
		void Refresh() { m_frameIndex = 0; }
	private:
		CAnimation* Add(SFrame frame);

	};
}
