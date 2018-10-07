#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"

using namespace Framework::Component;

bool CRenderer::Init(CString texturePath)
{	
	m_texture = GameManager::IGameManager::GetInstance()->Get_Direct3DCore()->CreateTexture(texturePath);
	return m_texture != nullptr;
}

void CRenderer::Release()
{
	if (m_texture)
		m_texture->Release();
}

void CRenderer::Render()
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
