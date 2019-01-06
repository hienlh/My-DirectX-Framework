#pragma once
#include "stdafx.h"
#include "MonoBehavier.h"

enum class CameraState
{
	Normal,
	Following,
	MeetingBoss,
};

class CameraController : public Framework::CMonoBehavior
{
	//Public Properties
public:
	Framework::CGameObject *m_player = nullptr;
private:
	CameraState m_state = CameraState::Normal;
	std::vector<Bound> m_limitedBounds = {};
	std::vector<Bound> m_bossLimitedBounds = {};
	bool m_isFree = false;
	DWORD m_currentBound = 0;

private:
	CameraController() = default;
public:
	CameraController(const CameraController& cc);
	CameraController(Framework::CGameObject *game_object);
	~CameraController() = default;

public:
	CameraController* SetState(const CameraState& state) { m_state = state; return this; }
	CameraController* SetIsFree(const bool &isFree) { this->m_isFree = isFree; return this; }

	CameraState GetState() const { return m_state; }

public:
	void Update(DWORD dt) override;
	void Render() override;

	CameraController* Clone() override { return new CameraController(*this); }

	void Follow(DWORD dt);
	void MeetBoss(DWORD dt, int indexMinBound);
};
