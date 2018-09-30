#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Macros.h"

namespace Framework
{
	namespace Component
	{
		// Enum for builder
		enum EComponentType
		{
			UNKNOWN = 0,
			TRANSFORM = 1,
			RENDERER = 3
		};

		// Initialize parameters for Render Component
		struct SRendererBuilder
		{
			LPDIRECT3DDEVICE9 d3ddev = nullptr;
			LPCSTR texturePath = nullptr;
		};

		// Initialize parameters for Transform Component
		struct STransformBuilder
		{
			D3DXVECTOR3 position = VECTOR3_ZERO;
			D3DXVECTOR3 rotation = VECTOR3_ZERO;
			D3DXVECTOR3 scale = VECTOR3_ZERO;
		};

		union UBuilderData
		{
			SRendererBuilder rendererBuilder;
			STransformBuilder transformBuilder;
		};

		// Builder Struct
		struct SBuilder
		{
			EComponentType m_componentType = EComponentType::UNKNOWN;
			UBuilderData m_data;

			SBuilder(EComponentType componentType, UBuilderData data) : m_componentType(componentType), m_data(data) {}
		};

		// Component Class
		class CComponent
		{
			// Properties
		private:
			EComponentType m_componentType = EComponentType::UNKNOWN;

			// Cons / Des
		public:
			CComponent() = default;
			virtual ~CComponent() = default;

			//
		public:
			static CComponent* Instantiate(const SBuilder &builder);
			static void Release(CComponent* pObject);
		};
	}
}
