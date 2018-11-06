#include "stdafx.h"
#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"

using namespace Framework;

void CRenderer::SetTexture(LPCWSTR texture_path)
{
	Init(texture_path);
}

bool CRenderer::Init(LPCWSTR texturePath)
{
	m_pTexture = CGraphic::GetInstance()->CreateTexture(texturePath, m_textureWidth, m_textureHeight);
	return m_pTexture != nullptr;
}

void CRenderer::Release()
{
	if (m_pTexture)
		m_pTexture->Release();
}

void CRenderer::Update(DWORD dt)
{
	
}

void CRenderer::Render()
{
	if (m_pGameObject == nullptr) return;

	const auto transform = m_pGameObject->GetComponent<CTransform>();
	if (m_pTexture == nullptr || transform == nullptr) return;

	//If dev don't set width height then draw with default width, height of image
	if (m_textureWidth == -1 || m_textureHeight == -1)
		CGraphic::GetInstance()->Draw(m_pTexture, &transform->Get_Position());
	else
		CGraphic::GetInstance()->Draw(m_pTexture, &transform->Get_Position(), new Rect(Vector2(0,0), Vector2(m_textureWidth, m_textureHeight)));
}

void CRenderer::Destroy(CRenderer* &instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
