#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Graphic.h"

using namespace Framework;

CCamera::CCamera(const CCamera &camera) : CComponent(camera)
{
	m_Name = camera.m_Name;
	m_width = camera.m_width;
	m_height = camera.m_height;
	m_angle = camera.m_angle;
	m_identityMatrix = camera.m_identityMatrix;
	m_orthographicMatrix = camera.m_orthographicMatrix;
	m_scaleFactors = camera.m_scaleFactors;
	m_viewMatrix = camera.m_viewMatrix;
}

Framework::CCamera::CCamera(CGameObject* gameObject) : CComponent(gameObject)
{
	m_width = SCREEN_WIDTH;
	m_height = SCREEN_HEIGHT;
	m_angle = 0;
	m_scaleFactors = Vector3(1, 1, 1);
	D3DXMatrixOrthoLH(&m_orthographicMatrix, m_width, -m_height, -100, 100);
	D3DXMatrixIdentity(&m_identityMatrix);
}

Framework::CCamera::CCamera(CGameObject* gameObject, int width, int height, float angle, Vector3 scaleFactors) : CComponent(gameObject)
{
	m_width = width;
	m_height = height;
	m_angle = angle;
	m_scaleFactors = scaleFactors;
	D3DXMatrixOrthoLH(&m_orthographicMatrix, width, -height, -100, 100);
	D3DXMatrixIdentity(&m_identityMatrix);
}

void Framework::CCamera::Update(DWORD dt)
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

CCamera* CCamera::Clone() const
{
	return new CCamera(*this);
}
