#pragma once
#include <MonoBehavier.h>
using namespace Framework;
class BlastHornetChildController :
	public CMonoBehavior
{
	// Cons Des
public:
	BlastHornetChildController(CGameObject *gameObject);
	~BlastHornetChildController() = default;

	// override
private:

	void Update(DWORD dt) override;
	void Render() override;
};

