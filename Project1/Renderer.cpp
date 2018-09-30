#include "Renderer.h"
#include "Macros.h"
#include "Direct3DCore.h"

using namespace Framework::Component;

bool CRenderer::Init(LPCSTR texturePath)
{
	m_texture = Base::IDirect3DCore::GetInstance()->CreateTexture(texturePath);
	return m_texture == nullptr ? false : true;
}

void CRenderer::Destroy()
{
	if (m_texture)
		m_texture->Release();
}

CRenderer* CRenderer::Instantiate(LPCSTR texturePath)
{
	CRenderer* pRenderer = nullptr;
	SAFE_ALLOC(pRenderer, CRenderer);

	if (!pRenderer->Init(texturePath))
		SAFE_DELETE(pRenderer);

	return pRenderer;
}

void CRenderer::Release(CRenderer* pObject)
{
	pObject->Destroy();
	SAFE_DELETE(pObject);
}

void CRenderer::Update(Vector3 position)
{
	Base::IDirect3DCore::GetInstance()->Draw(position.x, position.y, m_texture);
}
