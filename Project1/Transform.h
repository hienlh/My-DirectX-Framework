#pragma once
#include "header.h"
#include "Component.h"
namespace Framework
{
	namespace Component
	{
		class CTransform : public CComponent
		{
		public:
			Vector3 position;
			Vector3 localPosition;
			Vector3 rotation;
			Vector3 localRotation;
			Vector3 localScale;

		public:
			CTransform() = default;
			virtual ~CTransform() = default;

		private:
			bool Init(Vector3 position);
			bool Init(Vector3 position, Vector3 rotation, Vector3 local_scale);
			void Release();

		public:
			static CTransform* Instantiate(Vector3 position, Vector3 rotation, Vector3 local_scale);
			static void Destroy(CTransform *OTranform);

			void Update();
		};
	}
}
