#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Macros.h"

class EffectPool
{
private:
	static EffectPool *__instance;
	
private:
	std::map<std::string, Framework::CGameObject*[EFFECT_POOL_SIZE]> m_pools = {};

public:
	void AddNewEffect(const std::string &prefabName);
	Framework::CGameObject* CreateEffect(const std::string &prefabName, const Vector2& position);

public:
	static EffectPool* GetInstance() { if(!__instance) __instance = new EffectPool(); return __instance; }


};
