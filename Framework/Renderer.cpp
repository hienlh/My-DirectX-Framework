#include "stdafx.h"
#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"

using namespace Framework;

bool CRenderer::Init(CWString texturePath)
{
	m_texture = 
		CGraphic::GetInstance()->CreateTexture(texturePath);
	return m_texture != nullptr;
}

void CRenderer::Release()
{
	if (m_texture)
		m_texture->Release();
}

CRenderer* CRenderer::Instantiate(Framework::UObjectData data)
{
	CRenderer* instance = nullptr;
	SAFE_ALLOC(instance, CRenderer);

	instance->m_type = EObjectType::RENDERER;

	if (!instance->Init(data.renderData.texturePath))
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
	CGraphic::GetInstance()->Draw(VECTOR3_ZERO, m_texture);
}

void CRenderer::Render()
{
	CTransform* transform = reinterpret_cast<CGameObject*>(m_parentObject)->GetTranform();
	CGraphic::GetInstance()->Draw({ transform->m_position.x, transform->m_position.y,0 }, m_texture);
}
