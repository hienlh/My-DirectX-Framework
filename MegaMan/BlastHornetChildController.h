#pragma once
#include <MonoBehavier.h>
#include <time.h>
using namespace Framework;
class BlastHornetChildController : public CMonoBehavior
{
private:
	int  destroyTime = 5000;
	int aliveTime;
	bool isStart = false;
	int blood = 50;
	// Cons Des
public:

	explicit BlastHornetChildController(const CMonoBehavior& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{

	}

	explicit BlastHornetChildController(CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{

	}

	BlastHornetChildController* Clone()  override { return new BlastHornetChildController(*this); }

	// override
public:
	void OnTriggerEnter(CCollision* collision) override;
	void Update(const DWORD& dt) override;
	void Render() override;
	//
public:
	void SetAliveTime(int time) { aliveTime = time; }
	void Explosive();
};

