#include "stdafx.h"
#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"
#include "CTexture.h"
#include "ResourceManager.h"

using namespace Framework;

void CRenderer::SetTexture(LPCWSTR texture_name)
{
	Init(texture_name);
}

bool CRenderer::Init(LPCWSTR textureName)
{
	m_pTexture = CResourceManager::GetInstance()->GetTexture(textureName);
	m_textureWidth = m_pTexture->width;
	m_textureHeight = m_pTexture->height;
	return m_pTexture != nullptr;
}

void CRenderer::Release()
{
	delete m_pTexture;
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
		CGraphic::GetInstance()->Draw(m_pTexture, &transform->Get_Position(), nullptr, nullptr, transform->Get_Rotation().z);
	else
		CGraphic::GetInstance()->Draw(m_pTexture, &transform->Get_Position(), new Rect(Vector2(0,0), Vector2(m_textureWidth, m_textureHeight)), nullptr, transform->Get_Rotation().z);
}

void CRenderer::Destroy(CRenderer* &instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
