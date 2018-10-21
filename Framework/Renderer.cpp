#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"

using namespace Framework;

bool CRenderer::Init(LPCWSTR texturePath)
{
	m_pTexture = CGraphic::GetInstance()->CreateTexture(texturePath, m_textureWidth, m_textureHeight);
	return m_pTexture != nullptr;
}

void CRenderer::Release() const
{
	if (m_pTexture)
		m_pTexture->Release();
}

void CRenderer::Update(DWORD dt)
{
	
}

void CRenderer::Render()
{
	CTransform* pTransform = reinterpret_cast<CGameObject*>(m_parentObject)->GetTranform();
	CGraphic::GetInstance()->Draw(m_pTexture, pTransform->Get_Position());
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
