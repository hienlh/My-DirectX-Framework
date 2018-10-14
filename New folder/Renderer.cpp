#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"
#include "GameManager.h"
#include "Direct3DCore.h"

using namespace Framework::Component;

bool CRenderer::Init(LPCSTR texturePath)
{
	m_texture = Base::IGraphic::GetInstance()->CreateTexture(texturePath);
	return m_texture != nullptr;
}

void CRenderer::Release()
{
	if (m_texture)
		m_texture->Release();
}

CRenderer* CRenderer::Instantiate(Framework::Object::UObjectData data)
{
	CRenderer* instance = nullptr;
	SAFE_ALLOC(instance, CRenderer);

	instance->m_type = Object::EObjectType::RENDERER;

	if (instance->Init(data.renderData.texturePath))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

void CRenderer::Destroy(CRenderer* &instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}

void CRenderer::Update(DWORD dt)
{
	Base::IGraphic::GetInstance()->Draw(VECTOR3_ZERO, m_texture);
}

void CRenderer::Render()
{
	auto transform = _gameObject->GetTranform();
	Base::IGraphic::GetInstance()->Draw({ transform->m_position.x, transform->m_position.y,0 }, m_texture);
}
