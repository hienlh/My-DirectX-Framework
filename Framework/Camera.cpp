#include "Camera.h"
#include "GameObject.h"

Framework::CCamera::CCamera(CGameObject* gameObject) : CComponent(gameObject)
{
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	_angle = 0;
	_scaleFactors = Vector3(1, 1, 1);
	D3DXMatrixOrthoLH(&_orthographicMatrix, _width, -_height, 0, 1);
	D3DXMatrixIdentity(&_identityMatrix);
}

Framework::CCamera::CCamera(CGameObject* gameObject, int width, int height, float angle, Vector3 scaleFactors) : CComponent(gameObject)
{
	_width = width;
	_height = height;
	_angle = angle;
	_scaleFactors = scaleFactors;
	D3DXMatrixOrthoLH(&_orthographicMatrix, width, -height, 0, 1);
	D3DXMatrixIdentity(&_identityMatrix);
}

Framework::CCamera::~CCamera()
{
}

void Framework::CCamera::Update(DWORD dt)
{
	auto pos = _gameObject->GetComponent<CTransform>()->Get_Position();

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

