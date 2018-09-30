#include "Renderer.h"
#include "Macros.h"
#include "Direct3DCore.h"

using namespace Framework::Component;

bool CRenderer::Init(LPCSTR texturePath)
{
	bool result = false;
	Base::IDirect3DCore::GetInstance()->CreateTexture(texturePath) != nullptr ? result =  true : result = false;
	return result;
}

void CRenderer::Destroy()
{
	if (m_texture)
		m_texture->Release();	
}

CRenderer* CRenderer::Instantiate(LPDIRECT3DDEVICE9 d3ddev, LPCSTR texturePath)
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
