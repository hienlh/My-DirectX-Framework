#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Graphic.h"

using namespace Framework;

CCamera* CCamera::SetScale(const Vector2 &scale)
{
	m_scale = scale;

	m_scaleFactors = Vector3(m_scale.x, m_scale.y, 1);

	D3DXMatrixOrthoLH(&m_orthographicMatrix, m_size.x * m_scale.x, -m_size.y * m_scale.y, -100, 100);

	return this;
}

CCamera* CCamera::SetSize(const Vector2& size)
{
	m_size = size;
	
	D3DXMatrixOrthoLH(&m_orthographicMatrix, m_size.x * m_scale.x, -m_size.y * m_scale.y, -100, 100);

	return this;
}

CCamera::CCamera(const CCamera &camera) : CComponent(camera)
{
	m_Name = camera.m_Name;
	m_size = camera.m_size;
	m_angle = camera.m_angle;
	m_identityMatrix = camera.m_identityMatrix;
	m_orthographicMatrix = camera.m_orthographicMatrix;
	m_scaleFactors = camera.m_scaleFactors;
	m_viewMatrix = camera.m_viewMatrix;
}

Framework::CCamera::CCamera(CGameObject* gameObject) : CComponent(gameObject)
{
	m_angle = 0;
	SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
	SetScale(VECTOR2_ONE);
	D3DXMatrixIdentity(&m_identityMatrix);
}

void Framework::CCamera::Update(const DWORD &dt)
{
	auto pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();

	this->m_viewMatrix = Matrix(
		m_scaleFactors.x * cos(m_angle), m_scaleFactors.x * sin(m_angle), 0, 0,
		-m_scaleFactors.y * sin(m_angle), m_scaleFactors.y * cos(m_angle), 0, 0,
		0, 0, m_scaleFactors.z, 0,
		-pos.x * m_scaleFactors.x * cos(m_angle) + pos.y * m_scaleFactors.y * sin(m_angle), -pos.x * m_scaleFactors.y * sin(m_angle) - pos.y * m_scaleFactors.y * cos(m_angle), 0, 1
	);
}

void Framework::CCamera::Render()
{
	CGraphic::GetInstance()->DrawRectangle(Rect(m_pGameObject->GetComponent<CTransform>()->Get_Position(), { 256, 256 }, { 0.5,0.5 }), D3DCOLOR_XRGB(100, 100, 100));
}

CCamera& CCamera::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if(const auto pCam = dynamic_cast<const CCamera*>(&component))
	{
		m_angle = pCam->m_angle;
		m_identityMatrix = pCam->m_identityMatrix;
		m_orthographicMatrix = pCam->m_orthographicMatrix;
		m_scale = pCam->m_scale;
		m_scaleFactors = pCam->m_scaleFactors;
		m_size = pCam->m_size;
		m_viewMatrix = pCam->m_viewMatrix;
	}

	return *this;
}
