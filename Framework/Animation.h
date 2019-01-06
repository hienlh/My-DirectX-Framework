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
		void Update(DWORD dt) override;

		// Getter / Setter
	public:
		CSprite* GetSprite();
		bool IsLastFrame() const;
		bool GetIndexCurrentFrame() const { return m_frameIndex; }
		DWORD GetSpeed() const { return m_speed; }

		CAnimation* SetIndexCurrentFrame(int index);
		CAnimation* SetSpeed(DWORD speed) { m_speed = speed; return this; }

		//Method
	public:
		CAnimation* Add(std::string textureName, DWORD indexSprite, DWORD pos = -1, DWORD time = 0);
		CAnimation* Add(CSprite* sprite, DWORD pos = -1, DWORD time = 0);
		void Refresh() { m_frameIndex = 0; }
	private:
		CAnimation* Add(SFrame frame);

	};
}
