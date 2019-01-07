#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Macros.h"

class BulletPool
{
private:
	static BulletPool *__instance;

private:
	std::map<std::string, Framework::CGameObject*[BULLET_POOL_SIZE]> m_pools = {};

public:
	void AddNewTypeBullet(const std::string &prefabName);
	Framework::CGameObject* CreateBullet(const std::string &prefabName, const Vector2& position);

public:
	static BulletPool* GetInstance() { if (!__instance) __instance = new BulletPool(); return __instance; }

	
};
