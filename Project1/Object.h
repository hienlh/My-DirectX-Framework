#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macros.h"
#include "Header.h"

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
			RENDERER = 3,
			RIGIDBODY = 4
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
			Vector2 position = Vector2(0, 0);
			Vector3 rotation = VECTOR3_ZERO;
			Vector3 scale = VECTOR3_ZERO;
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
			UObjectData builderData = { {} };
		};

		// Object class
class CObject {
			// Properties
		protected:
			EObjectType m_type = EObjectType::UNKNOWN;

			// Cons / Des
		public:
			CObject() = default;
			virtual ~CObject() = default;

			// Abstract Classes
		public:
			virtual void Update(DWORD dt) = 0;
			virtual void Render() = 0;

			// Static methods
		public:
			static CObject* Instantiate(SBuilder builder);
			static void Destroy(CObject* &instance);
		};
	}
}
