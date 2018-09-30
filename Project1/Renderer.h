#pragma once
#include "Header.h"
#include "Component.h"

namespace Framework
{
	namespace Component
	{
		class CRenderer final : public CComponent
		{
			// Properties
		private:
			LPDIRECT3DTEXTURE9 m_texture = nullptr;

			// Cons / Des
		public:
			CRenderer() = default;
			virtual ~CRenderer() = default;

			// Internal methods
		private:
			bool Init(LPCSTR texturePath);
			void Destroy();

			// Static methods
		public:
			static CRenderer* Instantiate(LPDIRECT3DDEVICE9 d3ddev, LPCSTR texturePath);
			static void Release(CRenderer* pObject);
		};
	}
}
