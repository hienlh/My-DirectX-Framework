#include "GameLogicController.h"
#include "Macros.h"
#include "CanBeAttacked.h"

void GameLogicController::Start()
{
}

void GameLogicController::Update(const DWORD& dt)
{
	Framework::CScene* pScene = Framework::CGameManager::GetInstance()->GetCurrentScene();
	Framework::CGameObject* pPlayer = pScene->FindGameObject(Player);
	if (pPlayer)
	{
		// Player died
		if (!pPlayer->GetIsActive())
			PostQuitMessage(0);
	}	
}
