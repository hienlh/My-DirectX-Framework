#include "stdafx.h"

#include "Graphic.h"
#include "Macros.h"
#include "GameObject.h"

using namespace Framework;

CGraphic* CGraphic::__instance = nullptr;

void CGraphic::SetTransform(Matrix& orthographicMatrix, Matrix& identityMatrix, Matrix& viewMatrix)
{
	m_pDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	m_pDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

bool CGraphic::Init(HWND hWind, bool fullscreen)
{
	bool result = false;
	do
	{
		// initialize Direct3D
		m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!m_pDirect3D)
			break;
		
		// set Direct3D presentation parameters
		D3DPRESENT_PARAMETERS d3dpp;

		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.Windowed = !fullscreen;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.EnableAutoDepthStencil = TRUE;    // automatically run the z-buffer for us
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;    // 16-bit pixel format for the z-buffer

		RECT rect;
		GetClientRect(hWind, &rect); // retrieve Window width & height 

		d3dpp.BackBufferWidth = rect.right + 1;
		d3dpp.BackBufferHeight = rect.bottom + 1;
		d3dpp.hDeviceWindow = hWind;

		// create Direct3D device
		m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWind,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pDevice);

		if (!m_pDevice)
			break;

		m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
		
		// clear the back buffer to black
		m_pDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		// create pointer to the back buffer
		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
		if (!m_pBackBuffer)
			break;
		
		// Initialize sprite helper from Direct3DX helper library
		D3DXCreateSprite(m_pDevice, &m_pSpriteHandler);
		if (!m_pSpriteHandler)
			break;
		
		result = true;
	} while (false);

	return result;
}

void CGraphic::Release()
{
	if (m_pDirect3D)
		m_pDirect3D->Release();

	if (m_pDevice)
		m_pDevice->Release();

	if (m_pBackBuffer)
		m_pBackBuffer->Release();

	if (m_pSpriteHandler)
		m_pSpriteHandler->Release();

	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();
}

bool CGraphic::Render(CScene * scene) const
{
	bool result = false;
	do
	{
		m_pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		// Start rendering
		m_pDevice->BeginScene();
		// Clear back buffer with black color
		m_pDevice->ColorFill(m_pBackBuffer, nullptr, COLOR_BLACK);

		m_pSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // D3DXSPRITE_SORT_DEPTH_BACKTOFRONT

		for (CGameObject* pGameObject : scene->GetAllGameObjects())
			if(pGameObject->GetIsActive())
				pGameObject->Render();

		if(scene->GetIsRenderQuadTree())
			scene->GetQuadTree()->Render();

		m_pSpriteHandler->End();

		// stop rendering
		m_pDevice->EndScene();

		// display back buffer content to the screen
		m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);

		result = true;
	} while (false);

	return result;
}

void CGraphic::Draw(Texture* texture, Vector3 *position, Rect* pSourceRect, Vector2* center, float angle, DWORD fillColor, Vector3 *scale, bool flipX, bool flipY) const
{
	Vector3 *center3D = center ? new Vector3(center->x, center->y, 0) : nullptr;
	RECT* pRect = new RECT();

	D3DXMATRIX matCombined;
	D3DXMatrixIdentity(&matCombined);

	D3DXMATRIX matRotate;
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(angle));
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale,
		(flipX ? -1 : 1) * (scale ? scale->x : 1),
		(flipY ? -1 : 1) * (scale ? scale->y : 1),
		scale ? scale->z : 1);
	D3DXMATRIX matTranslate;
	D3DXMatrixTranslation(&matTranslate, position->x, position->y, position->z);

	matCombined *= matRotate;
	matCombined *= matScale;
	matCombined *= matTranslate;

	m_pSpriteHandler->SetTransform(&matCombined);

	if (pSourceRect) {
		pRect->top = pSourceRect->top;
		pRect->left = pSourceRect->left;
		pRect->right = pSourceRect->right;
		pRect->bottom = pSourceRect->bottom;
	}
	m_pSpriteHandler->Draw(texture->texture, pRect, center3D, nullptr, fillColor);

}

void CGraphic::Draw(CSprite* sprite, Vector3* position, float angle, Vector3 *scale, bool flipX, bool flipY, DWORD fillColor, DWORD alpha) const
{
	Texture* texture = sprite->GetTexture();
	const Vector2 anchor = sprite->GetAnchor();
	Rect sourceRect = sprite->GetSourceRect();
	Vector2 center = Vector2(anchor.x * (sourceRect.right - sourceRect.left), 
							   anchor.y * (sourceRect.bottom - sourceRect.top));
	if(fillColor!=COLOR_WHITE)
	{
		int a = alpha;
		int r = COLOR_GET_R(fillColor);
		int b = COLOR_GET_B(fillColor);
		int g = COLOR_GET_G(fillColor);
		CDebug::Log(static_cast<long>(a));
	}

	const DWORD _fillColor = D3DCOLOR_RGBA(COLOR_GET_R(fillColor), COLOR_GET_G(fillColor), COLOR_GET_B(fillColor), alpha);

	Draw(texture, position, &sourceRect, &center, angle, _fillColor, scale, flipX, flipY);
}

void CGraphic::Init_VertexGraphic(std::vector<CUSTOMVERTEX> vertices)
{
	size_t size = vertices.size() * sizeof(CUSTOMVERTEX);

	// create the vertex and store the pointer into v_buffer, which is created globally
	m_pDevice->CreateVertexBuffer(size,
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);

	VOID* pVoid;    // the void pointer
	m_pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);    // lock the vertex buffer
	memcpy(pVoid, vertices.data(), size);    // copy the vertices to the locked buffer
	m_pVertexBuffer->Unlock();    // unlock the vertex buffer
}

void CGraphic::DrawRectangle(Rect rect, DWORD color)
{
	// Refer: http://directxtutorial.com/Lesson.aspx?lessonid=9-4-4
	// create some vertices using the CUSTOMVERTEX struct built earlier
	std::vector<CUSTOMVERTEX> vertices;
	if(color)	
		vertices = {
			{ rect.left, rect.top, -100, color },
			{ rect.right, rect.top, -100, color },
			{ rect.right, rect.bottom, -100, color },
			{ rect.left, rect.bottom, -100, color },
			{ rect.left, rect.top, -100, color },
		};
	else 
		vertices = {
			{ rect.left, rect.top, -100, D3DCOLOR_XRGB(0, 0, 255) },
			{ rect.right, rect.top, -100, D3DCOLOR_XRGB(0, 255, 0) },
			{ rect.right, rect.bottom, -100, D3DCOLOR_XRGB(255, 255, 255) },
			{ rect.left, rect.bottom, -100, D3DCOLOR_XRGB(255, 0, 0) },
			{ rect.left, rect.top, -100, D3DCOLOR_XRGB(0, 0, 255) },
		};

	Init_VertexGraphic(vertices);

	// select which vertex format we are using
	m_pDevice->SetFVF(CUSTOMFVF);

	// select the vertex buffer to display
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));

	// copy the vertex buffer to the back buffer
	m_pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
}

Texture* CGraphic::CreateTexture(std::string texturePath, D3DCOLOR transparentColor) const
{
	Texture* m_texture = new Texture();
	do
	{
		D3DXIMAGE_INFO info;
		HRESULT hr = D3DXGetImageInfoFromFileA(texturePath.c_str(), &info);
		if (hr != S_OK)
			break;

		m_texture->width = info.Width;
		m_texture->height = info.Height;
		hr = D3DXCreateTextureFromFileExA(
			m_pDevice,       // Pointer to Direct3D device object
			texturePath.c_str(), // Path to the image to load
			info.Width,  // CTexture width
			info.Height, // CTexture height
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			transparentColor, // Transparent color
			&info,
			nullptr,
			&m_texture->texture // Created texture pointer

		);

		if (hr != S_OK)
			break;
		
	} while (false);

	return m_texture;
}

void CGraphic::Instantiate(HWND hWnd, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGraphic);

		if (!__instance->Init(hWnd, fullscreen))
		{
			__instance->Release();
			SAFE_DELETE(__instance);
		}
	}
}

void CGraphic::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CGraphic* CGraphic::GetInstance()
{
	return __instance;
}
