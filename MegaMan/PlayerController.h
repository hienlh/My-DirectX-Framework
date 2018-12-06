#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class PlayerController : public CMonoBehavior
{
public:
	enum EUniqueStateCode
	{
		IDLE		= 0b10000,
		RUN			= 0b01000,
		//RUN_FAST	= 0b00100,
		JUMP		= 0b00100,
		FALL		= 0b00010,
		//MOVE_LEFT	= 0b00000100,
		//MOVE_RIGHT	= 0b00000010,
		SHOOT		= 0b000001,
	};

	enum EStateCode
	{
		S_IDLE			= IDLE,
		S_RUN			= RUN,
		S_IDLE_SHOOT	= IDLE | SHOOT,
		S_RUN_SHOOT		= RUN | SHOOT,
		S_JUMP			= JUMP,
		S_FALL			= FALL,
		S_JUMP_SHOOT	= JUMP | SHOOT,
		S_FALL_SHOOT	= FALL | SHOOT,
	};

private:
	DWORD m_stateCode;

	//Cons / Des
private:
	PlayerController() = default;

public:
	PlayerController(CGameObject *gameObject);
	~PlayerController() = default;

	int GetState() const { return m_stateCode; }
	void UpdateState(DWORD state, bool flag);

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;
};
