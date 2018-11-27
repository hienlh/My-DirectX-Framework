#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "CameraController.h"
#include "PlayerController.h"
#include "ResourceManager.h"

#pragma comment(lib, "Framework.lib")

using namespace Framework;
using namespace std;

void ParseXML(const char* fileName, vector<Rect> &info, size_t depth)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	tinyxml2::XMLElement* parent = doc.FirstChildElement();
	for (size_t iDepth = 0; iDepth < depth - 1; iDepth++)
		parent = parent->FirstChildElement();

	// Count sprites stored in xml for resize
	size_t spriteCount = 0;
	for (tinyxml2::XMLNode* node = parent->FirstChild(); node; node = node->NextSibling())
		spriteCount++;

	info.resize(spriteCount);

	// Load attributes
	tinyxml2::XMLElement* child = parent->FirstChildElement();
	for (size_t iSprite = 0; iSprite < info.size(); iSprite++)
	{
		info[iSprite] = { Vector2(child->IntAttribute("x"), child->IntAttribute("y")),
									Vector2(child->IntAttribute("w"), child->IntAttribute("h")) };
		child = child->NextSiblingElement();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	CScene* pScene = CScene::Instantiate();
	pGameManager->SetCurrentScene(pScene);
	pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	pScene->GetMainCamera()->AddComponent<CameraController>();

	CResourceManager *pResourceManager = CResourceManager::GetInstance();

	pResourceManager->AddTexture(L"Megaman Left", L".\\Resources\\megaman_left.png");
	pResourceManager->AddTexture(L"Megaman Right", L".\\Resources\\megaman_right.png");
	pResourceManager->AddTexture(L"Background", L".\\Resources\\mini_background.png");
	pResourceManager->AddTexture(L"Intro Enemies", L".\\Resources\\Intro Enemies.png");

	// Player
	vector<Rect> megaman_left, megaman_right;
	ParseXML(".\\Resources\\megaman_left.xml", megaman_left, 2);
	ParseXML(".\\Resources\\megaman_right.xml", megaman_right, 2);

	CAnimation* anim = CAnimation::Instantiate(L"Megaman Run Left", L"Megaman Left", 100);
	for (size_t iAnimation = 18; iAnimation < 18 + 11; iAnimation++)
		anim->Add(megaman_left[iAnimation], 0.05f);

	anim = CAnimation::Instantiate(L"Megaman Run Right", L"Megaman Right", 100);
	for (size_t iAnimation = 18; iAnimation < 18 + 11; iAnimation++)
		anim->Add(megaman_right[iAnimation], 0.05f);

	anim = CAnimation::Instantiate(L"Megaman Idle Left", L"Megaman Left", 100);
	anim->Add(megaman_left[10], 0.05f);

	anim = CAnimation::Instantiate(L"Megaman Idle Right", L"Megaman Right", 100);
	anim->Add(megaman_right[12], 0.05f);

	// Grounds
	vector<Rect> grounds;
	ParseXML(".\\Resources\\mini_background.xml", grounds, 2);

	for (size_t iGround = 0; iGround < grounds.size(); iGround++)
	{
		CGameObject* pGround = CGameObject::Instantiate((wstring(L"Ground") + to_wstring(iGround)).c_str(),
			Vector2(grounds[iGround].left, grounds[iGround].top));
		pGround->AddComponent<CRigidbody>()->SetGravityScale(0);
		pGround->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pGround->GetComponent<CBoxCollider>()->SetSize(Vector2(grounds[iGround].right - grounds[iGround].left, 
			grounds[iGround].bottom - grounds[iGround].top));
	}

	CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
	pBackground->AddComponent<CRenderer>()->SetTexture(L"Background");

	// Player components
	CGameObject* pPlayer = CGameObject::Instantiate(L"Player", Vector2(100, 0));
	pPlayer->GetComponent<CTransform>()->Set_Rotation(Vector3(0, 0, 0));
	pPlayer->AddComponent<CAnimator>()->AddAnimation(L"Megaman Idle Right");
	pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Idle Left");
	pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Run Left");
	pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Run Right");
	pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
	pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
	pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(25, 35));
	pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(false);
	pPlayer->AddComponent<PlayerController>();

	CGameObject* pCamera = pScene->GetMainCamera();
	pCamera->GetComponent<CameraController>()->m_target = pPlayer;
	pCamera->GetComponent<CameraController>()->SetIsFollow(true);
	pGameManager->Run();

	// Enermies
	/*vector<Rect> enemies;
	ParseXML(".\\Resources\\Intro Enemies.xml", grounds, 2);

	anim = CAnimation::Instantiate(L"Enemies", L"Intro Enemies", 100);
	for (size_t iAnimation = 18; iAnimation < 18 + 11; iAnimation++)
		anim->Add(enemies[iAnimation], 0.05f);
*/
	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();

	return 0;
}
