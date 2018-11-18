#pragma once
#include "stdafx.h"
#include "MonoBehavier.h"

class CameraController : public Framework::CMonoBehavior
{
	//Public Properties
public:
	Framework::CGameObject *m_target;
private:
	bool isFollow = false;

private:
	CameraController() = default;
public:
	CameraController(Framework::CGameObject *game_object);
	~CameraController() = default;

public:
	void SetIsFollow(bool isFollow) { this->isFollow = isFollow; }

public:
	void Update(DWORD dt) override;
	void Render() override;

	void Following();
};
