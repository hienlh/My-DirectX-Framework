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

	NotorBangerEnemyController& operator=(const CComponent& component) override;

	//Cons / Des
public:
	NotorBangerEnemyController(CGameObject *gameObject) : CMonoBehavior(gameObject) {};
	~NotorBangerEnemyController() = default;

	//Getter / Setter
public:
	NotorBangerEnemyController* SetSpeed(float speed) { m_speed = speed; return this; }

	float GetSpeed() const { return m_speed; }
	void SetTarget(CGameObject* targer) { m_target = targer; }
	Vector2 CalculateVelocity(const Vector2 &myPosition, const Vector2 &targetPosition, const float &gravity, const float &vy) const;
	std::string CalculateAngelRotation(const Vector2 &velocity) const;

	//Override
private:
	void OnCollisionEnter(CCollision* collision) override;
	void Update(const DWORD &dt) override;
};

