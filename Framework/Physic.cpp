#include "stdafx.h"
#include "Physic.h"
#include "Scene.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "GameManager.h"
#include <string>

using namespace Framework;

CPhysic* CPhysic::__instance = nullptr;

void CPhysic::RegisterObserver(CPhysicObserver* observer)
{
	const auto component = dynamic_cast<CComponent*>(observer);
	if(component)
	{
		if (component->m_pGameObject->GetScene() != CGameManager::GetInstance()->GetCurrentScene())
			return;
	}

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
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider) 
			{
				observer->OnCollisionEnter(collision);
			}
			else if ( component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnCollisionEnter(collision->Swap());
			}
		}
		else observer->OnCollisionEnter(collision);
	}

	//SAFE_DELETE(collision);
}

void CPhysic::NotifyCollisionExit(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider)
			{
				observer->OnCollisionExit(collision);
			}
			else if (component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnCollisionExit(collision->Swap());
			}
		}
		else observer->OnCollisionExit(collision);
	}

	//SAFE_DELETE(collision);
}

void CPhysic::NotifyCollisionStay(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider)
			{
				observer->OnCollisionStay(collision);
			}
			else if (component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnCollisionStay(collision->Swap());
			}
		}
		else observer->OnCollisionStay(collision);
	}

	//SAFE_DELETE(collision);
}

void CPhysic::NotifyTriggerEnter(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider)
			{
				observer->OnTriggerEnter(collision);
			}
			else if (component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnTriggerEnter(collision->Swap());
			}
		}
		else observer->OnTriggerEnter(collision);
	}

	//SAFE_DELETE(collision);
}

void CPhysic::NotifyTriggerExit(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider)
			{
				observer->OnTriggerExit(collision);
			}
			else if (component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnTriggerExit(collision->Swap());
			}
		}
		else observer->OnTriggerExit(collision);
	}

	//SAFE_DELETE(collision);
}

void CPhysic::NotifyTriggerStay(CCollision* collision)
{
	for (CPhysicObserver* observer : m_observers)
	{
		const auto component = dynamic_cast<CComponent*>(observer);
		if (component)
		{
			if (component->m_pGameObject == collision->m_pCollider)
			{
				observer->OnTriggerStay(collision);
			}
			else if (component->m_pGameObject == collision->m_pOtherCollider)
			{
				observer->OnTriggerStay(collision->Swap());
			}
		}
		else observer->OnTriggerStay(collision);
	}

	//SAFE_DELETE(collision);
}

CPhysic* CPhysic::GetInstance()
{
	if (!__instance)
		SAFE_ALLOC(__instance, CPhysic);

	return __instance;
}

void CPhysic::Destroy()
{
	SAFE_DELETE(__instance);
}

bool CPhysic::IsOverlapping(const Bound& object, const Bound& other)
{
	const float left = other.left - object.right;
	const float top = other.bottom - object.top;
	const float right = other.right - object.left;
	const float bottom = other.top - object.bottom;

	return !(left >= 0 || right <= 0 || top <= 0 || bottom >= 0);
}

void CPhysic::Update(DWORD dt)
{
	// Collision test

	//Dynamic GameObject
	CScene* currentScreen = CGameManager::GetInstance()->GetCurrentScene();
	auto listDynamicGameObject = currentScreen->GetListDynamicGameObject();

	for (auto i = listDynamicGameObject.begin(); i != listDynamicGameObject.end(); ++i)
	{
		//Update Gravity
		if (CRigidbody* rigid = (*i)->GetComponent<CRigidbody>())
		{
			if (!rigid->GetIsKinematic())
				rigid->m_velocity.y += rigid->GetGravityScale() * GRAVITY*dt;
		}

		//test with QuadTree
		const Bound bound = (*i)->GetComponent<CCollider>()->GetBoundGlobal();
		std::set<CGameObject*> listReturnByQuadTree = currentScreen->GetQuadTree()->query(bound);

		for (CGameObject* const otherObject : listReturnByQuadTree)
		{
			SweptAABBx(dt, *i, otherObject);
		}

		//test with others
		for (auto j = i; j != listDynamicGameObject.end(); ++j)
		{
			if (i != j) {
				SweptAABBx(dt, *i, *j);
			}
		}
	}

	//Half-Static GameObjects
	auto listHalfStaticGameObject = currentScreen->GetListHalfStaticGameObject();
	for (auto game_object : listHalfStaticGameObject)
	{
		//Update Gravity
		if (CRigidbody* rigid = game_object->GetComponent<CRigidbody>())
		{
			if (!rigid->GetIsKinematic())
				rigid->m_velocity.y += rigid->GetGravityScale() * GRAVITY;
		}

		const Bound bound = game_object->GetComponent<CCollider>()->GetBoundGlobal();
		std::set<CGameObject*> listReturnByQuadTree = currentScreen->GetQuadTree()->query(bound);

		for (auto otherObject : listReturnByQuadTree)
		{
			if (otherObject != game_object) {
				SweptAABBx(dt, game_object, otherObject);
			}
		}
	}

}

float CPhysic::SweptAABBx(const DWORD dt, CGameObject* moveObject, CGameObject* staticObject)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	if(strstr(moveObject->GetName().c_str(), std::string("Bullet").c_str()) && strstr(staticObject->GetName().c_str(), std::string("Bullet").c_str()))
	{
  		int a = 10;
	}
	if (!moveObject->GetIsActive() || !staticObject->GetIsActive()) return -1;

	staticObject->GetComponent<CCollider>()->GetBoundGlobal().GetBound(st, sl, sr, sb);
	moveObject->GetComponent<CCollider>()->GetBoundGlobal().GetBound(mt, ml, mr, mb);

	const bool mEffect = moveObject->GetComponent<CCollider>()->GetUsedByEffector();
	const bool sEffect = staticObject->GetComponent<CCollider>()->GetUsedByEffector();

	const bool mTrigger = moveObject->GetComponent<CCollider>()->GetIsTrigger();
	const bool sTrigger = staticObject->GetComponent<CCollider>()->GetIsTrigger();
	const bool isTrigger = mTrigger || sTrigger;

	const bool mKinematic = moveObject->GetComponent<CRigidbody>()->GetIsKinematic();
	const bool sKinematic = staticObject->GetComponent<CRigidbody>()->GetIsKinematic();

	Vector2 mv = moveObject->GetComponent<CRigidbody>()->GetVelocity();
	Vector2 sv = staticObject->GetComponent<CRigidbody>()->GetVelocity();
	const Vector2 dv = (mv - sv) * dt;
	const float dx = dv.x;
	const float dy = dv.y;

	if (dx != 0 || dy != 0)
		if (!Bound(mt, ml, mb, mr).intersect(Bound(st, sl, sb, sr))) {
			auto nextBound = Bound(mt + dy, ml + dx, mb + dy, mr + dx);
			if (nextBound.intersect(Bound(st, sl, sb, sr)))
			{
				!isTrigger
					? NotifyCollisionEnter(new CCollision(moveObject, staticObject))
					: NotifyTriggerEnter(new CCollision(moveObject, staticObject));
			}
		}

	SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	if (IsOverlapping(Bound(mt, ml, mb, mr), Bound(st, sl, sb, sr)) && t < 0 && !isTrigger)
	{
		OverLapResponse(moveObject, staticObject, nx, ny);

		//deflect
		if (nx > 0 && dx < 0 || nx < 0 && dx > 0) {
			mv = Vector2(0, mv.y);
			sv = Vector2(0, sv.y);
		}
		if (ny > 0 && dy < 0 || ny < 0 && dy > 0) {
			mv = Vector2(mv.x, 0);
			sv = Vector2(sv.x, 0);
		}

		if (!mKinematic) moveObject->GetComponent<CRigidbody>()->SetVelocity(mv);
		if (!sKinematic) staticObject->GetComponent<CRigidbody>()->SetVelocity(sv);
		return t;
	}

	if (t >= 0 && t <= 1) {
		if (!isTrigger) {
			CTransform *mTran = moveObject->GetComponent<CTransform>();
			CTransform *sTran = staticObject->GetComponent<CTransform>();

			mTran->PlusPosition(mv * dt * t);
			sTran->PlusPosition(sv * dt * t);

			const float rt = 1 - t;

			//deflect
			if (nx != 0) {
				mv = mEffect && !mKinematic ? Vector2(-mv.x, mv.y) : Vector2(0, mv.y);
				sv = sEffect && !sKinematic ? Vector2(-sv.x, sv.y) : Vector2(0, sv.y);
				if (mEffect && !mKinematic) mTran->PlusPosition(Vector2(mv.x, 0) * dt * rt);
				if (sEffect && !sKinematic) sTran->PlusPosition(Vector2(sv.x, 0) * dt * rt);
			}
			if (ny != 0) {
				mv = mEffect && !mKinematic ? Vector2(mv.x, -mv.y) : Vector2(mv.x, 0);
				sv = sEffect && !sKinematic ? Vector2(sv.x, -sv.y) : Vector2(sv.x, 0);
				if (mEffect && !mKinematic) mTran->PlusPosition(Vector2(0, mv.y) * dt * rt);
				if (sEffect && !sKinematic) sTran->PlusPosition(Vector2(0, sv.y) * dt * rt);
			}

			moveObject->GetComponent<CRigidbody>()->SetVelocity(mv);
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

	const float bl = dx > 0 ? ml : ml + dx;
	const float bt = dy > 0 ? mt : mt + dy;
	const float br = dx > 0 ? mr + dx : mr;
	const float bb = dy > 0 ? mb + dy : mb;
	if (br <= sl || bl >= sr || bb <= st || bt >= sb) return;

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
	// Comment Because: Continue calculate for process overlapping

	const float t_entry = max(tx_entry, ty_entry);
	const float t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f; //-1 left, 1 right
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f; // -1 top, 1 bottom
	}
}

/**
 * \brief Separate objects from one another
 * \param nx Direction of overlap of Object (1 left, -1 right)
 * \param ny Direction of overlap of Object (1 top, -1 bottom)
 */
void CPhysic::OverLapResponse(CGameObject* object, CGameObject* other, float &nx, float &ny)
{
	CBoxCollider *objectCollider = object->GetComponent<CBoxCollider>();
	CBoxCollider *otherCollider = other->GetComponent<CBoxCollider>();

	CTransform *objectTransform = object->GetComponent<CTransform>();
	CTransform *otherTransform = other->GetComponent<CTransform>();

	const bool objectKinematic = object->GetComponent<CRigidbody>()->GetIsKinematic();
	const bool otherKinematic = other->GetComponent<CRigidbody>()->GetIsKinematic();

	if (objectKinematic && otherKinematic) return;

	float ratio = 0.5; //Use 0.5 for 2 movable objects, 1 for only one movable object 

	if (objectKinematic || otherKinematic) ratio = 1;

	const Bound overLapBound = objectCollider->GetBoundGlobal().OverLapBound(otherCollider->GetBoundGlobal());

	if (overLapBound == Rect(0, 0, 0, 0)) return;

	const Bound ObjectColliderBound = objectCollider->GetBoundGlobal();
	const float _distanceTop = fabs(ObjectColliderBound.top - overLapBound.top);
	const float _distanceBottom = fabs(ObjectColliderBound.bottom - overLapBound.bottom);
	const float _distanceLeft = fabs(ObjectColliderBound.left - overLapBound.left);
	const float _distanceRight = fabs(ObjectColliderBound.right - overLapBound.right);

	if (_distanceTop < 0.0001 && _distanceBottom < 0.0001) ny = 0;
	else if (_distanceTop < 0.0001) ny = 1;
	else if (_distanceBottom < 0.0001) ny = -1;

	if (_distanceLeft < 0.0001 && _distanceRight < 0.0001) nx = 0;
	else if (_distanceLeft < 0.0001) nx = 1;
	else if (_distanceRight < 0.0001) nx = -1;

	if(overLapBound.Size().x > overLapBound.Size().y)
	{
		if(_distanceBottom < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(0, -ratio * overLapBound.Size().y));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(0, ratio * overLapBound.Size().y));
			nx = 0;
			return;
		}
		if(_distanceTop<0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(0, ratio * overLapBound.Size().y));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(0, -ratio * overLapBound.Size().y));
			nx = 0;
			return;
		}
	}
	else
	{
		if (_distanceRight < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(-ratio * overLapBound.Size().x, 0));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(ratio * overLapBound.Size().x, 0));
			ny = 0;
			return;
		}
		if (_distanceLeft < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(ratio * overLapBound.Size().x, 0));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(-ratio * overLapBound.Size().x, 0));
			ny = 0;
			return;
		}

		const float _maxDistance = max(max(_distanceTop, _distanceBottom), max(_distanceLeft, _distanceRight));

		if (fabs(_maxDistance - _distanceTop) < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(0, -ratio * overLapBound.Size().y));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(0, ratio * overLapBound.Size().y));
			nx = 0;
			return;
		}
		if (fabs(_maxDistance - _distanceBottom) < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(0, ratio * overLapBound.Size().y));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(0, -ratio * overLapBound.Size().y));
			nx = 0;
			return;
		}
		if (fabs(_maxDistance - _distanceLeft) < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(-ratio * overLapBound.Size().x, 0));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(ratio * overLapBound.Size().x, 0));
			ny = 0;
			return;
		}
		if (fabs(_maxDistance - _distanceRight) < 0.0001)
		{
			if (!objectKinematic) objectTransform->PlusPosition(Vector2(ratio * overLapBound.Size().x, 0));
			if (!otherKinematic) otherTransform->PlusPosition(Vector2(-ratio * overLapBound.Size().x, 0));
			ny = 0;
			return;
		}
	}
}
