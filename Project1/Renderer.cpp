#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"
#include "GameManager.h"

using namespace Framework::Component;

bool CRenderer::Init(LPCSTR texturePath)
{
	m_texture = Base::IDirect3DCore::GetInstance()->CreateTexture(texturePath);
	return m_texture != nullptr;
}

void CRenderer::Release()
{
	if (m_texture)
		m_texture->Release();
}

void CRenderer::Render()
CRenderer* CRenderer::Instantiate(Framework::Object::UObjectData data)
{
	GameManager::IGameManager::GetInstance()->Get_Direct3DCore()->Draw(m_parentObject->Get_Transform()->Get_Position(), m_texture);
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

	Base::IDirect3DCore::GetInstance()->Draw(0,0, m_texture);
}

void CRenderer::Render()
{
	auto transform = _gameObject->GetTranform();
	Base::IDirect3DCore::GetInstance()->Draw(transform->m_position.x, transform->m_position.y, m_texture);
}
