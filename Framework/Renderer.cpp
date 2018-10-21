#include "Renderer.h"
#include "Macros.h"
#include "Graphic.h"
#include "GameManager.h"

using namespace Framework;

void CRenderer::SetTexture(LPTSTR texture_path)
{
	Init(texture_path);
}

bool CRenderer::Init(LPCSTR texturePath)
{
	m_texture = CGraphic::GetInstance()->CreateTexture(texturePath);

	auto size = CGraphic::GetInstance()->GetImageSize(texturePath);
	_width = size.x;
	_height = size.y;

	return m_texture != nullptr;
}

void CRenderer::Release() const
{
	if (m_texture)
		m_texture->Release();
}

CRenderer* CRenderer::Instantiate()
{
	CRenderer* instance = nullptr;
	SAFE_ALLOC(instance, CRenderer);

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

	CGraphic::GetInstance()->Draw(0,0, m_texture);
}

void CRenderer::Render()
{
	if (_gameObject == nullptr) return;

	const auto transform = _gameObject->GetComponent<CTransform>();
	if (m_texture == nullptr || transform == nullptr) return;

	//If dev don't set width height then draw with default width, height of image
	if(_width == -1 || _height == -1)
		CGraphic::GetInstance()->Draw(transform->m_position.x, transform->m_position.y, m_texture);
	else
		CGraphic::GetInstance()->Draw(transform->m_position.x, transform->m_position.y, _width, _height, m_texture);
}
