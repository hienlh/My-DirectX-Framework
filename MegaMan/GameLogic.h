#pragma once
#include "GameObject.h"

class CGameLogic : public Framework::CGameObject
{
private:
	static CGameLogic* __instance;

private:
	CGameLogic(const std::string &name) : CGameObject(name, VECTOR2_ZERO, true) {}
	~CGameLogic() = default;

public:
	static CGameLogic* GetInstance() 
	{ 	
		return __instance;
	}

	static CGameLogic* Instantiate(const std::string &name)
	{
		if (!__instance)
			SAFE_ALLOC1(__instance, CGameLogic, name);
		
		return __instance;
	}
};
