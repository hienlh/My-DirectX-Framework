#include "../Framework/Macros.h"
#include "../Framework/Header.h"
#include "../Framework/GameManager.h"
#include "../Framework/GameObject.h"
#include "../Framework/Graphic.h"
#include "../Framework/Input.h"
#include "MarioController.h"
#include "BlockController.h"
#include "../Framework/Camera.h"
#include "CameraController.h"

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	auto* pGameManager = CGameManager::GetInstance();
	auto scene = CScene::Instantiate();
	pGameManager->SetCurrentScene(scene);
	scene->GetMainCamera()->AddComponent<CameraController>();

	do
	{
		CGameObject* Background = CGameObject::Instantiate(Vector2(0, 0));
		Background->AddComponent<CRenderer>();
		Background->GetComponent<CRenderer>()->SetTexture(String("Background.jpg"));

		CGameObject* mario = CGameObject::Instantiate(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

		mario->AddComponent<CRenderer>();
		mario->GetComponent<CRenderer>()->SetTexture(String("mario.png"));

		mario->AddComponent<CRigidbody>();
		mario->GetComponent<CRigidbody>()->SetVelocity(Vector2(1, 1));
		mario->AddComponent<MarioController>();

		CGameObject* leftblock = CGameObject::Instantiate(Vector2(0, 0));
		leftblock->AddComponent<CRenderer>();
		leftblock->GetComponent<CRenderer>()->SetTexture(String("Block.png"));

		leftblock->AddComponent<CRigidbody>();
		leftblock->GetComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));

		leftblock->AddComponent<BlockController>();
		leftblock->GetComponent<BlockController>()->SetAllParameters(true, false);

		CGameObject* rightblock = CGameObject::Instantiate(Vector2(SCREEN_WIDTH - 10, 0));
		rightblock->AddComponent<CRenderer>();
		rightblock->GetComponent<CRenderer>()->SetTexture(String("Block.png"));

		rightblock->AddComponent<CRigidbody>();
		rightblock->GetComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));

		rightblock->AddComponent<BlockController>();
		rightblock->GetComponent<BlockController>()->SetAllParameters(true, true);

		mario->GetComponent<MarioController>()->leftBlock = leftblock;
		mario->GetComponent<MarioController>()->rightBlock = rightblock;


		scene->GetMainCamera()->GetComponent<CameraController>()->m_target = mario;
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();

	return 0;
}
