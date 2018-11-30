#include "stdafx.h"
#include "Physic.h"
#include "Scene.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "GameManager.h"
#include <string>

using namespace Framework;

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

bool CPhysic::IsOverlapping(const Bound& object, const Bound& other)
{
	float left = other.left - object.right;
	float top = other.bottom - object.top;
	float right = other.right - object.left;
	float bottom = other.top - object.bottom;

	return !(left >= 0 || right <= 0 || top <= 0 || bottom >= 0);
}

void CPhysic::Update(DWORD dt)
{
	//TODO make 2 objects not overlap each other, if they overlap, move movable object

	auto list = CGameManager::GetInstance()->GetCurrentScene()->GetListGameObject();
	for (CGameObject* const game_object : list)
	{
		if (CRigidbody* rigid = game_object->GetComponent<CRigidbody>())
		{
			rigid->_velocity.y += rigid->GetGravityScale() * GRAVITY;
		}
	}

	CScene* currentScreen = CGameManager::GetInstance()->GetCurrentScene();
	auto listCollierObject = currentScreen->GetListColliderObject();
	for (CGameObject* const object : listCollierObject)
	{
		const Bound bound = object->GetComponent<CCollider>()->GetBoundGlobal();
		std::list<CGameObject*> listReturnByQuadTree = currentScreen->GetQuadTree()->query(bound);

		for (CGameObject* const otherObject : listReturnByQuadTree)
		{
			if (otherObject != object) {
				SweptAABBx(dt, object, otherObject);
			}
		}
	}
}

float CPhysic::SweptAABBx(DWORD dt, CGameObject* moveObject, CGameObject* staticObject)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	staticObject->GetComponent<CCollider>()->GetBoundGlobal().GetBound(st, sl, sr, sb);
	moveObject->GetComponent<CCollider>()->GetBoundGlobal().GetBound(mt, ml, mr, mb);

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

	if (IsOverlapping(Bound(mt, ml, mb, mr), Bound(st, sl, sb, sr)) && t != 0) 
	{
		auto a = moveObject->GetComponent<CTransform>()->Get_Position();
		//CDebug::Log("Move (%f, %f)\n", a.x, a.y);
		a = staticObject->GetComponent<CTransform>()->Get_Position();
		//CDebug::Log("Static (%f, %f)\n", a.x, a.y);
		auto b = IsOverlapping(Bound(mt, ml, mb, mr), Bound(st, sl, sb, sr));
		moveObject->GetComponent<CTransform>()->PlusPosition(mv * dt * t - mv*dt*0.01);
		staticObject->GetComponent<CTransform>()->PlusPosition(sv * dt * t - sv * dt*0.01);
		//deflect
		if (nx != 0) {
			mv = Vector2(0, mv.y);
			sv = Vector2(0, sv.y);
		}
		if (ny != 0) {
			mv = Vector2(mv.x, 0);
			sv = Vector2(sv.x, 0);
		}

		moveObject->GetComponent<CRigidbody>()->SetVelocity(mv);
		staticObject->GetComponent<CRigidbody>()->SetVelocity(sv);
		return t;
	}

	if (t >= 0 && t < 1) {
		if(t > 0) NotifyCollisionEnter(new CCollision(moveObject, staticObject));

		const bool mEffect = moveObject->GetComponent<CCollider>()->GetUsedByEffector();
		const bool sEffect = staticObject->GetComponent<CCollider>()->GetUsedByEffector();
		CTransform *mTran = moveObject->GetComponent<CTransform>();
		CTransform *sTran = staticObject->GetComponent<CTransform>();

		mTran->PlusPosition(mv * dt * t);
		sTran->PlusPosition(sv * dt * t);

		float rt = 1 - t;

		//deflect
		if (nx != 0) {
			mv = mEffect ? Vector2(-mv.x, mv.y) : Vector2(0, mv.y);
			sv = sEffect ? Vector2(-sv.x, sv.y) : Vector2(0, sv.y);
			if (mEffect) mTran->PlusPosition(Vector2(mv.x, 0) * dt * rt);
			if (sEffect) sTran->PlusPosition(Vector2(sv.x, 0) * dt * rt);
		}
		if (ny != 0) {
			mv = mEffect ? Vector2(mv.x, -mv.y) : Vector2(mv.x, 0);
			sv = sEffect ? Vector2(sv.x, -sv.y) : Vector2(sv.x, 0);
			if (mEffect) mTran->PlusPosition(Vector2(0, mv.y) * dt * rt);
			if (sEffect) sTran->PlusPosition(Vector2(0, sv.y) * dt * rt);
		}

		moveObject->GetComponent<CRigidbody>()->SetVelocity(mv);
		staticObject->GetComponent<CRigidbody>()->SetVelocity(sv);

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


	//if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

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