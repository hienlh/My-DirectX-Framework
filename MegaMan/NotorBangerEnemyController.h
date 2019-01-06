#pragma once
#include "MonoBehavier.h"
#include "GameObject.h"

using namespace Framework;

class NotorBangerEnemyController : public CMonoBehavior
{
private:
	float m_speed = 0;
	CGameObject* m_target = nullptr;
	DWORD m_reloadTime = 0;

	// To Clone Function
private:
	NotorBangerEnemyController() = default;
	NotorBangerEnemyController(const NotorBangerEnemyController &PC);
	NotorBangerEnemyController* Clone() override { return new NotorBangerEnemyController(*this); }

	//Cons / Des
public:
	NotorBangerEnemyController(CGameObject *gameObject) : CMonoBehavior(gameObject) {};
	~NotorBangerEnemyController() = default;

	//Getter / Setter
public:
	NotorBangerEnemyController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }
	void SetTarget(CGameObject* targer) { m_target = targer; }
	Vector2 CalculateVeclocity(Vector2 myPosition, Vector2 targetPosition,float gravity, float Vy);
	std::string CalculateAngelRotation(Vector2 velocity);
	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(DWORD dt) override;
	void Render() override;

};

