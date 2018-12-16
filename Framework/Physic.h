#pragma once
#include "PhysicObserver.h"

namespace Framework {
	class CScene;
	class CGameObject;

	class CPhysic
	{
	private:
		static CPhysic* __instance;

		//Cons / Des
	private:
		CPhysic() = default;
		void Release();
	public:
		~CPhysic() = default;

		// Observer Pattern
	private:
		std::vector <CPhysicObserver *> m_observers;
	public:
		void RegisterObserver(CPhysicObserver *observer);
		void RemoveObserver(CPhysicObserver *observer);
	private:
		void NotifyCollisionEnter(CCollision* collision);
		void NotifyCollisionExit(CCollision* collision);
		void NotifyCollisionStay(CCollision* collision);
		void NotifyTriggerEnter(CCollision* collision);
		void NotifyTriggerExit(CCollision* collision);
		void NotifyTriggerStay(CCollision* collision);

	public:
		static CPhysic* GetInstance();
		static void Destroy();
		static bool IsOverlapping(const Bound& object, const Bound& other);

		void Update(DWORD dt);

		//Internal
	private:
		/*Return time collision and output vector2 normal*/
		float SweptAABBx(DWORD dt, CGameObject *moveObject, CGameObject *staticObject);
		void SweptAABB(
			float ml, float mt, float mr, float mb,
			float dx, float dy,
			float sl, float st, float sr, float sb,
			float &t, float &nx, float &ny);
		static void OverLapResponse(CGameObject* object, CGameObject* other);
	};
}
