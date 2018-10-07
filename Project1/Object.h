#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macros.h"

namespace Framework
{
	namespace Object
	{
		// Enum for builder
		enum EBuilderType
		{
			UNKNOWN = 0,
			GAMEOBJECT = 1,
			TRANSFORM = 2,
			RENDERER = 3
		};

		// Initialize parameters for Game Object
		struct SGameObjectBuilder {};

		// Initialize parameters for Render Component
		struct SRendererBuilder
		{
			LPCSTR texturePath = nullptr;
		};

		// Initialize parameters for Transform Component
		struct STransformBuilder
		{
			D3DXVECTOR3 position = VECTOR3_ZERO;
			D3DXVECTOR3 rotation = VECTOR3_ZERO;
			D3DXVECTOR3 scale = VECTOR3_ZERO;
		};

		// Builder
		union UBuilderData
		{
			SGameObjectBuilder gameObjectBuilder;
			SRendererBuilder rendererBuilder;
			STransformBuilder transformBuilder;
		};

		// Builder Struct
		struct SBuilder
		{
			EBuilderType m_componentType = EBuilderType::UNKNOWN;
			UBuilderData m_data;

			//SBuilder(EBuilderType componentType, UBuilderData data) : m_componentType(componentType), m_data(data) {}
		};

		// Object class
		class CObject
		{
			// Properties
		protected:
			EBuilderType m_builderType = EBuilderType::UNKNOWN;

			// Cons / Des
		public:
			CObject() = default;
			~CObject() = default;

			// Abstract Classes
		public:
			virtual void Update(DWORD dt) = 0;
			virtual void Render() = 0;

			// Static methods
		public:
			static CObject* Instantiate(const SBuilder &builder);
			static void Release(CObject* &instance);
		};
	}
}
