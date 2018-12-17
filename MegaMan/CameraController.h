#pragma once
#include "stdafx.h"
#include "MonoBehavier.h"

class CameraController : public Framework::CMonoBehavior
{
	//Public Properties
public:
	Framework::CGameObject *m_target = nullptr;
private:
	bool m_isFollow = false;
	std::vector<Bound> m_limitedBound = {};

private:
	CameraController() = default;
public:
	CameraController(Framework::CGameObject *game_object);
	~CameraController() = default;

public:
	void SetIsFollow(bool isFollow) { this->m_isFollow = isFollow; }

public:
	void Update(DWORD dt) override;
	void Render() override;

	CameraController* Clone() const override;

	void Following();
};
