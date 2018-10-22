#include "Physic.h"
#include "Scene.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "GameManager.h"
#include <string>

CPhysic* CPhysic::__instance = nullptr;

void CPhysic::Release()
{
}

void CPhysic::RegisterObserver(CPhysicObserver* observer)
{
	m_observers.push_back(observer);
}

void CPhysic::RemoveObserver(CPhysicObserver* observer)
{
	const int count = m_observers.size();
	int i;

	for (i = 0; i < count; i++) {
		if (m_observers[i] == observer)
			break;
	}
	if (i < count)
		m_observers.erase(m_observers.begin() + i);
}

void CPhysic::NotifyCollisionEnter(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnCollisionEnter(collision);
	}
}

void CPhysic::NotifyCollisionExit(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnCollisionExit(collision);
	}
}

void CPhysic::NotifyCollisionStay(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnCollisionStay(collision);
	}
}

void CPhysic::NotifyTriggerEnter(CCollider* other)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnTriggerEnter(other);
	}
}

void CPhysic::NotifyTriggerExit(CCollider* other)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnTriggerExit(other);
	}
}

void CPhysic::NotifyTriggerStay(CCollider* other)
{
	for (CPhysicObserver* observer : m_observers)
	{
		observer->OnTriggerStay(other);
	}
}

CPhysic* CPhysic::GetInstance()
{
	if (!__instance)
		SAFE_ALLOC(__instance, CPhysic);

	return __instance;
}

void CPhysic::Destroy()
{
	__instance->Release();
	SAFE_DELETE(__instance);
}

void CPhysic::Update(DWORD dt)
{
	auto list = CGameManager::GetInstance()->GetCurrentScene()->GetListColliderObject();
	for (auto i = list.begin(); i != list.end(); ++i)
	{
		for (auto j = i; j != list.end(); ++j)
		{
			if (i != j) {
				SweptAABBx(dt, *i, *j);
			}
		}
	}
}

float CPhysic::SweptAABBx(DWORD dt, CGameObject* moveObject, CGameObject* staticObject)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	staticObject->GetComponent<CCollider>()->GetBoundGlobal().GetBounds(st, sl, sr, sb);
	moveObject->GetComponent<CCollider>()->GetBoundGlobal().GetBounds(mt, ml, mr, mb);

	Vector2 mv = moveObject->GetComponent<CRigidbody>()->GetVelocity();
	Vector2 sv = staticObject->GetComponent<CRigidbody>()->GetVelocity();
	const Vector2 dv = (mv - sv) * dt;
	const float dx = dv.x;
	const float dy = dv.y;

	SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	if (t > 0 && t < 1) {
		NotifyCollisionEnter(new CCollision(moveObject, staticObject));

		const bool mEffect = moveObject->GetComponent<CCollider>()->GetUsedByEffector();
		const bool sEffect = staticObject->GetComponent<CCollider>()->GetUsedByEffector();
		CTransform *mTran = moveObject->GetComponent<CTransform>();
		CTransform *sTran = staticObject->GetComponent<CTransform>();

		if (mEffect) {
			mTran->PlusPosition(mv * dt * t);
		}
		if (sEffect) {
			sTran->PlusPosition(sv * dt * t);
		}

		float rt = 1 - t;

		//deflect
		if (nx != 0) {
			mv = Vector2(-mv.x, mv.y);
			sv = Vector2(-sv.x, sv.y);
			if (mEffect) mTran->PlusPosition(Vector2(mv.x, 0) * dt * rt);
			if (sEffect) sTran->PlusPosition(Vector2(sv.x, 0) * dt * rt);
		}
		if (ny != 0) {
			mv = Vector2(mv.x, -mv.y);
			sv = Vector2(sv.x, -sv.y);
			if (mEffect) mTran->PlusPosition(Vector2(0, mv.y) * dt * rt);
			if (sEffect) sTran->PlusPosition(Vector2(0, sv.y) * dt * rt);
		}

		if (mEffect) {
			moveObject->GetComponent<CRigidbody>()->SetVelocity(mv);
		}
		if (sEffect) {
			staticObject->GetComponent<CRigidbody>()->SetVelocity(sv);
		}

	}
	return t;
}

void CPhysic::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{
	float dx_entry = 0, dx_exit = 0, tx_entry, tx_exit;
	float dy_entry = 0, dy_exit = 0, ty_entry, ty_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -std::numeric_limits<float>::infinity();
		tx_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -std::numeric_limits<float>::infinity();
		ty_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	const float t_entry = max(tx_entry, ty_entry);
	const float t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}