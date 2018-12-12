#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

using namespace Framework;

CCamera::CCamera(const CCamera &camera) : CComponent(camera)
{
	m_Name = camera.m_Name;
	_width = camera._width;
	_height = camera._height;
	_angle = camera._angle;
	_identityMatrix = camera._identityMatrix;
	_orthographicMatrix = camera._orthographicMatrix;
	_scaleFactors = camera._scaleFactors;
	_viewMatrix = camera._viewMatrix;
}

Framework::CCamera::CCamera(CGameObject* gameObject) : CComponent(gameObject)
{
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	_angle = 0;
	_scaleFactors = Vector3(1, 1, 1);
	D3DXMatrixOrthoLH(&_orthographicMatrix, _width, -_height, -100, 100);
	D3DXMatrixIdentity(&_identityMatrix);
}

Framework::CCamera::CCamera(CGameObject* gameObject, int width, int height, float angle, Vector3 scaleFactors) : CComponent(gameObject)
{
	_width = width;
	_height = height;
	_angle = angle;
	_scaleFactors = scaleFactors;
	D3DXMatrixOrthoLH(&_orthographicMatrix, width, -height, -100, 100);
	D3DXMatrixIdentity(&_identityMatrix);
}

void Framework::CCamera::Update(DWORD dt)
{
	auto pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();

	this->_viewMatrix = Matrix(
		_scaleFactors.x * cos(_angle), _scaleFactors.x * sin(_angle), 0, 0,
		-_scaleFactors.y * sin(_angle), _scaleFactors.y * cos(_angle), 0, 0,
		0, 0, _scaleFactors.z, 0,
		-pos.x * _scaleFactors.x * cos(_angle) + pos.y * _scaleFactors.y * sin(_angle), -pos.x * _scaleFactors.y * sin(_angle) - pos.y * _scaleFactors.y * cos(_angle), 0, 1
	);
}

void Framework::CCamera::Render()
{
}

CCamera* CCamera::Clone() const
{
	return new CCamera(*this);
}
