#include "stdafx.h"
#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Animator.h"

using namespace Framework;

CRenderer* CRenderer::SetSprite(CWString textureName, DWORD index)
{
	m_pRootSprite = CResourceManager::GetInstance()->GetSprite(textureName, index);
	m_pSprite = m_pRootSprite;
	return this;
}

bool CRenderer::Init(CWString textureName, DWORD index)
{
	m_pRootSprite = CResourceManager::GetInstance()->GetSprite(textureName, index);
	m_pSprite = m_pRootSprite;
	return m_pRootSprite != nullptr;
}

void CRenderer::Release() const
{
	delete m_pSprite;
	delete m_pRootSprite;
}

void CRenderer::Update(DWORD dt)
{
	if (CAnimator* anim = m_pGameObject->GetComponent<CAnimator>())
		m_pSprite = anim->GetCurrentSprite();
	else m_pSprite = m_pRootSprite;
}

void CRenderer::Render()
{
	if (m_pGameObject == nullptr) return;
	const auto transform = m_pGameObject->GetComponent<CTransform>();
	if (!m_pSprite || !transform) return;

	Vector3 scale = Vector3(transform->Get_Scale());

	Vector3 position3D = Vector3(transform->Get_Position());
	position3D.z = m_zOrder;

	CGraphic::GetInstance()->Draw(m_pSprite, &position3D, transform->Get_Rotation().z, &scale, m_flipX, m_flipY);
}

void CRenderer::Destroy(CRenderer* &instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
