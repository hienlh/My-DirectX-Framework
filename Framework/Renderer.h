#pragma once
#include "Object.h"
#include "Component.h"

namespace Framework {
	class CGameObject;
}

namespace Framework
{
	class CGameObject;

	class CRenderer final : public CComponent
	{
		// Properties
	private:
		Texture* m_pTexture = nullptr;
		DWORD m_textureWidth = 0, m_textureHeight = 0;
		
		// Cons / Des
	private:
		CRenderer() = default;
		virtual ~CRenderer() = default;

		// Internal methods
	private:
		bool Init(LPCWSTR texturePath);
		void Release();

	public:
		void Update(DWORD dt) override;
		void Render();

		// Static methods
	public:
		static CRenderer* Instantiate(UObjectData data);
		static void Destroy(CRenderer* &instance);

		// Override method
	public:

	};
}