#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macros.h"

namespace Framework
{
	namespace Object
	{
		// Enum for builder
		enum EObjectType
		{
			UNKNOWN = 0,
			GAME_OBJECT = 1,
			TRANSFORM = 2,
			RENDERER = 3
		};

		// Initialize parameters for Game Object
		struct SGameObjectBuilder
		{
		};

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
		union UObjectData
		{
			SGameObjectBuilder gameObjectData;
			SRendererBuilder renderData;
			STransformBuilder transformData;
		};

		// Builder Struct
		struct SBuilder
		{
			EObjectType builderType = EObjectType::UNKNOWN;
			UObjectData builderData = {{}};
		};

		// Object class
		class CObject
		{
			// Properties
		protected:
			EObjectType m_type = EObjectType::UNKNOWN;

			// Cons / Des
		public:
			CObject() = default;
			virtual ~CObject() = default;

		public:
			virtual void Update() = 0;

			// Static methods
		public:
			static CObject* Instantiate(SBuilder builder);
			static void Destroy(CObject* &instance);
		};
	}
}
