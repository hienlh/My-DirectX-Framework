#include "CameraController.h"
#include "../Framework/GameObject.h"
#include "Graphic.h"
#include "Camera.h"

CameraController::CameraController(const CameraController& cc) : CMonoBehavior(cc)
{
	m_player = cc.m_player;
	m_currentBound = cc.m_currentBound;
	m_state = cc.m_state;
	m_isFree = cc.m_isFree;
	m_limitedBounds = cc.m_limitedBounds;
}

CameraController::CameraController(Framework::CGameObject* game_object) : CMonoBehavior(game_object)
{
	m_limitedBounds.push_back({ { 0 + 128,768 + 128 }, { 1024 - 256,256 - 256 } });
	m_limitedBounds.push_back({ { 768 + 128,256 + 128 }, { 256 - 256,768 - 256 } });
	m_limitedBounds.push_back({ { 768 + 128,256 + 128 }, { 1536 - 256,256 - 256 } });
	m_limitedBounds.push_back({ { 1264 + 128,0 + 128 }, { 256 - 256,512 - 256 } });
	m_limitedBounds.push_back({ { 1536 + 128,256 + 128 }, { 768 - 256,1024 - 256 } });
	m_limitedBounds.push_back({ { 1536 + 128,1024 + 128 }, { 784 - 256,0 } });
	m_limitedBounds.push_back({ { 2304 + 128,1024 + 128 }, { 0,0 } });
	m_limitedBounds.push_back({ { 2560 + 128,1024 + 128 }, { 976 - 256,0 } });
	m_limitedBounds.push_back({ { 2816 + 128,768 + 128 }, { 2816 - 256,512 - 256 } });
	m_limitedBounds.push_back({ { 5632 + 128,1024 + 128 }, { 0,0 } });
	m_limitedBounds.push_back({ { 5888 + 128,1024 + 128 }, { 0,1024 -256 } });
	m_limitedBounds.push_back({ { 5888 + 128,1792 + 128 }, { 1566 - 256,0 } });
	m_limitedBounds.push_back({ { 7440 + 128,1792 + 128 }, { 0,0 } });
	m_limitedBounds.push_back({ { 7680 + 128,1792 + 128 }, { 0,0 } });

	/*m_bossLimitedBounds.push_back({ {2304 + 128,1024 + 128},{0,0} });
	m_bossLimitedBounds.push_back({ {5634 + 128,1024 + 128},{0,0} });
	m_bossLimitedBounds.push_back({ {7680 + 128,1792 + 128},{0,0} });*/
}

void CameraController::Update(DWORD dt)
{
	switch (m_state)
	{
	case CameraState::Following:
		Follow(dt);
		break;
	case CameraState::MeetingBoss: {
		/*int minBound = 0;
		const int limitBoundSize = m_bossLimitedBounds.size();
		const Vector2 pos = m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position();
		for (int i = 1; i < limitBoundSize; i++)
		{
			if (m_bossLimitedBounds[i].Distance(pos) < m_bossLimitedBounds[minBound].Distance(pos))
				minBound = i;
		}
		MeetBoss(dt, minBound);*/

		Follow(dt);
		break; 
	}
	default: ;
	}
}

void CameraController::Render()
{
	for (const Bound bound : m_limitedBounds)
	{
		Framework::CGraphic::GetInstance()->DrawRectangle(bound, D3DCOLOR_XRGB(50, 100, 150));
	}
}

void CameraController::Follow(DWORD dt)
{
	auto transform = m_pGameObject->GetComponent<Framework::CTransform>();

	if (m_isFree)
	{
		transform->Set_Position(m_player->GetComponent<Framework::CTransform>()->Get_Position());
		return;
	}

	const Vector2 camPosition = transform->Get_Position();
	const Vector2 camSize = m_pGameObject->GetComponent<Framework::CCamera>()->GetSize();
	Bound canViewArea = { m_limitedBounds[m_currentBound].TopLeft() - camSize / 4, m_limitedBounds[m_currentBound].Size() + camSize / 2 };
	const Vector2 targetPosition = m_player->GetComponent<Framework::CTransform>()->Get_Position();

	const bool canViewTarget(canViewArea.intersect({ targetPosition, {0,0} }));

	if (!canViewTarget) {
		const int limitBoundSize = m_limitedBounds.size();

		for (int i = 0; i < limitBoundSize; i++)
		{
			if (i != m_currentBound)
				if (m_limitedBounds[i].Distance(targetPosition) < m_limitedBounds[m_currentBound].Distance(targetPosition))
					m_currentBound = i;
		}
	}

	Vector2 newCamPos = targetPosition;
	if (targetPosition.x > m_limitedBounds[m_currentBound].right) newCamPos.x = m_limitedBounds[m_currentBound].right;
	else if (targetPosition.x < m_limitedBounds[m_currentBound].left) newCamPos.x = m_limitedBounds[m_currentBound].left;

	if (targetPosition.y > m_limitedBounds[m_currentBound].bottom) newCamPos.y = m_limitedBounds[m_currentBound].bottom;
	else if (targetPosition.y < m_limitedBounds[m_currentBound].top) newCamPos.y = m_limitedBounds[m_currentBound].top;

	//transform->Set_Position(camPosition);
	const Vector2 direction = newCamPos - camPosition;
	transform->Translate(direction * dt / 500);
}

void CameraController::MeetBoss(DWORD dt, int indexMinBound)
{
	const Vector2 direction = m_bossLimitedBounds[indexMinBound].TopLeft() - m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position();
	if(direction != Vector2(0,0))
		m_pGameObject->GetComponent<Framework::CTransform>()->Translate(direction * dt / 700);
}
