#pragma once
#include "PhysicObserver.h"
#include "PhysicSubject.h"

namespace Framework {
	class CScene;
	class CGameObject;

	class CPhysic : public CPhysicSubject
	{
	private:
		static CPhysic* __instance;

		//Cons / Des
	private:
		CPhysic() = default;
	public:
		~CPhysic() = default;

		// Observer Pattern
	/*private:
		std::vector <CPhysicObserver *> m_observers;
	public:
		void RegisterObserver(CPhysicObserver *observer);
		void RemoveObserver(CPhysicObserver *observer);*/
	private:
		void NotifyCollisionEnter(CCollision* collision) override;
		void NotifyCollisionExit(CCollision* collision) override;
		void NotifyCollisionStay(CCollision* collision) override;
		void NotifyTriggerEnter(CCollision* collision) override;
		void NotifyTriggerExit(CCollision* collision) override;
		void NotifyTriggerStay(CCollision* collision) override;

	public:
		static CPhysic* GetInstance();
		static void Destroy();
		static bool IsOverlapping(const Bound& object, const Bound& other);

		void Update(const DWORD &dt);

		//Internal
	private:
		/*Return time collision and output vector2 normal*/
		void SweptAABBx(const DWORD &dt, CGameObject *moveObject, CGameObject *staticObject);
		static void SweptAABB(
			float ml, float mt, float mr, float mb,
			float dx, float dy,
			float sl, float st, float sr, float sb,
			float &t, float &nx, float &ny);

		static void OverLapResponse(CGameObject* object, CGameObject* other, float &nx, float &ny);
	};
}
