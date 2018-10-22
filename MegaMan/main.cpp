#include "../Framework/Macros.h"
#include "../Framework/Header.h"
#include "../Framework/GameManager.h"
#include "../Framework/GameObject.h"
#include "../Framework/Graphic.h"
#include "../Framework/Input.h"
#include "../Framework/Rigidbody.h"
#include "../Framework/BoxCollider.h"
#include "../Framework/Camera.h"
#include "MarioController.h"
#include "BlockController.h"
#include "CameraController.h"

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	auto* pGameManager = CGameManager::GetInstance();
	auto scene = CScene::Instantiate();
	pGameManager->SetCurrentScene(scene);
	scene->GetMainCamera()->AddComponent<CameraController>();
	scene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	do
	{
		CGameObject* Background = CGameObject::Instantiate(String("Background"), Vector2(0, 0));
		CGameObject* mario = CGameObject::Instantiate(String("Mario"), Vector2(SCREEN_WIDTH / 2, 0));
		CGameObject* mario2 = CGameObject::Instantiate(String("Mario2"), Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 27));
		CGameObject* leftblock = CGameObject::Instantiate(String("Left Block"), Vector2(50, 0));
		CGameObject* rightblock = CGameObject::Instantiate(String("Right Block"), Vector2(SCREEN_WIDTH - 60, 0));

		Background->AddComponent<CRenderer>()->SetTexture(String("Background.jpg"));

		mario->AddComponent<CRenderer>()->SetTexture(String("mario.png"));
		mario->AddComponent<CRigidbody>()->SetVelocity(Vector2(.1, .1));
		mario->AddComponent<CBoxCollider>();
		mario->AddComponent<MarioController>()->leftBlock = leftblock;
		mario->GetComponent<MarioController>()->rightBlock = rightblock;

		mario2->AddComponent<CRenderer>()->SetTexture(String("mario.png"));
		mario2->AddComponent<CRigidbody>()->SetVelocity(Vector2(.1, -.1));
		mario2->AddComponent<CBoxCollider>();
		mario2->AddComponent<MarioController>()->leftBlock = leftblock;
		mario2->GetComponent<MarioController>()->rightBlock = rightblock;

		leftblock->AddComponent<CRenderer>()->SetTexture(String("Block.png"));
		leftblock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		leftblock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		leftblock->AddComponent<BlockController>()->SetAllParameters(true, false);

		rightblock->AddComponent<CRenderer>()->SetTexture(String("Block.png"));
		rightblock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		rightblock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		rightblock->AddComponent<BlockController>()->SetAllParameters(true, true);

		//scene->GetMainCamera()->GetComponent<CameraController>()->m_target = mario;
		scene->AddGameObjects(4, mario, mario2, leftblock, rightblock);

		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();

	return 0;
}
