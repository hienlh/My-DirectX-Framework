#pragma once
#include "../Framework/Component.h"

using namespace Framework;

class MarioController : public CComponent
{
private:
	CGameObject* _gameObject = nullptr;

public:
	MarioController(CGameObject *game_object) { _gameObject = game_object; }
	~MarioController() = default;

public:
	void Update(DWORD dt) override;
	void Render() override;
};

