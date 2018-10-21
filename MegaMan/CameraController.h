#pragma once
#include "../Framework/Component.h"

using namespace Framework;

class CameraController : public CComponent
{
	//Public Properties
public:
	CGameObject *m_target;

public:
	CameraController(CGameObject *game_object);
	~CameraController() = default;

public:
	void Update(DWORD dt) override;
	void Render() override;

	void Following();
};
