#include "Transform.h"

using namespace Framework::Component;

bool CTransform::Init(Vector2 position)
{
	this->position = position;
	this->rotation = Vector3(0, 0, 0);
	this->localScale = Vector3(1, 1, 1);
	return true;
}

bool Framework::Component::CTransform::Init(const Vector2 position, const Vector3 rotation, const Vector3 local_scale)
{
	this->position = position;
	this->rotation = rotation;
	this->localScale = local_scale;
	return true;
}

void CTransform::Release()
{

}

CTransform* CTransform::Instantiate(const Vector2 position, const Vector3 rotation, const Vector3 local_scale)
{
	CTransform* pTransform = nullptr;
	SAFE_ALLOC(pTransform, CTransform);
	if (!pTransform->Init(position, rotation, local_scale))
		SAFE_DELETE(pTransform);

	return pTransform;
}

void Framework::Component::CTransform::Destroy(CTransform *OTranform)
{
	OTranform->Release();
	SAFE_DELETE(OTranform);
}

void CTransform::Update(DWORD dt)
{

}

void CTransform::Render()
{
}
