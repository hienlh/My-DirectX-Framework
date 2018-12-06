#include "stdafx.h"
#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"
#include "CTexture.h"
#include "ResourceManager.h"

using namespace Framework;

CRenderer* CRenderer::SetTexture(LPCWSTR texture_name)
{
	Init(texture_name);
	return this;
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

	Vector3 scale = Vector3(transform->Get_Scale());

	Vector3 position3D = Vector3(transform->Get_Position());
	position3D.z = m_zOrder;

	//If dev don't set width height then draw with default width, height of image
	if (m_textureWidth == -1 || m_textureHeight == -1)
		CGraphic::GetInstance()->Draw(m_pTexture, &position3D, nullptr, false, false, nullptr, transform->Get_Rotation().z);
	else
		CGraphic::GetInstance()->Draw(m_pTexture, &position3D, new Rect(Vector2(m_renderPosX, m_renderPosY), Vector2(m_textureWidth, m_textureHeight)), 
			m_flipX, m_flipY, nullptr, transform->Get_Rotation().z);
}

void CRenderer::Destroy(CRenderer* &instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_FREE(instance);
	}
}
