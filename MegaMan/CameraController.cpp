#include "CameraController.h"
#include "../Framework/GameObject.h"
#include "Graphic.h"

CameraController::CameraController(Framework::CGameObject* game_object) : CMonoBehavior(game_object)
{
	m_limitedBound.push_back(Bound(896, 128, 896, 896));
	m_limitedBound.push_back(Bound(384, 896, 896, 896));
	m_limitedBound.push_back(Bound(890, 640, 896, 896));
	m_limitedBound.push_back(Bound({ 896, 384 }, { 1537, 0 }));
	m_limitedBound.push_back(Bound({ 1350, 128 }, { 1412-1350, 384-128 }));
	m_limitedBound.push_back(Bound({ 1535+128, 128 }, { 769, 1024 }));
}

void CameraController::Update(DWORD dt)
{
	auto transform = m_pGameObject->GetComponent<Framework::CTransform>();

	if (m_isFollow)
	{
		const Vector2 direction = m_target->GetComponent<Framework::CTransform>()->Get_Position()
							- m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position();
		transform->Translate(direction * dt / 500);
		//m_pGameObject->GetComponent<Framework::CTransform>()->Set_Position(m_target->GetComponent<Framework::CTransform>()->Get_Position());
	}

	Vector2 position = transform->Get_Position();

	bool insideBound = false;
	int indexNearestBound = 0;

	const int limitBoundSize = m_limitedBound.size();
	for(int i = 0 ;i<limitBoundSize;i++)
	{
		if (m_limitedBound[i].intersect(Bound(position, { 0,0 })))
		{
			insideBound = true;
			break;
		}
		
		if (m_limitedBound[i].Distance(position) < m_limitedBound[indexNearestBound].Distance(position))
			indexNearestBound = i;
	}

	if (!insideBound) 
	{
		if (position.x > m_limitedBound[indexNearestBound].right) position.x = m_limitedBound[indexNearestBound].right;
		else if (position.x < m_limitedBound[indexNearestBound].left) position.x = m_limitedBound[indexNearestBound].left;

		if (position.y > m_limitedBound[indexNearestBound].bottom) position.y = m_limitedBound[indexNearestBound].bottom;
		else if (position.y < m_limitedBound[indexNearestBound].top) position.y = m_limitedBound[indexNearestBound].top;

		transform->Set_Position(position);
		/*const Vector2 direction = position - m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position();
		transform->Translate(direction * dt / 10);*/
	}
}

void CameraController::Render()
{
	for (Bound bound : m_limitedBound)
	{
		Framework::CGraphic::GetInstance()->DrawRectangle(bound, D3DCOLOR_XRGB(50, 100, 150));
	}
}

CameraController* CameraController::Clone() const
{
	return new CameraController(*this);
}

void CameraController::Following()
{
	if(m_target)
	{
		m_pGameObject->GetComponent<Framework::CTransform>()->Set_Position(m_target->GetComponent<Framework::CTransform>()->Get_Position());
	}
}
