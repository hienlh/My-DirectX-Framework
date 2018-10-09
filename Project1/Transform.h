#pragma once
#include "Header.h"
#include "Component.h"
namespace Framework
{
	namespace Component
	{
		class CTransform final : public Object::CComponent
		{
		public:
			Vector2 m_position = VECTOR2_ZERO;
			Vector2 m_localPosition = VECTOR2_ZERO;
			Vector3 m_rotation = VECTOR3_ZERO;
			Vector3 m_localRotation = VECTOR3_ZERO;
			Vector3 m_scale = VECTOR3_ONE;
			Vector3 m_localScale = VECTOR3_ONE;

			Vector3 m_rotation = VECTOR3_ZERO;
			Vector3 m_localRotation = VECTOR3_ZERO;
			
			Vector3 m_scale = VECTOR3_ONE;
			Vector3 m_localScale = VECTOR3_ONE;

			// Cons / Des
		public:
			CTransform() = default;
			virtual ~CTransform() = default;

			// Getters / Setters
		public:
			Vector3 Get_Position() { return m_position; }
			Vector3 Get_Rotation() { return m_rotation; }
			Vector3 Get_Scale() { return m_scale; }

			void Set_Position(Vector3 position) { m_position = position; }
			void Set_Rotation(Vector3 rotation) { m_rotation = rotation; }
			void Set_Scale(Vector3 scale) { m_scale = scale; }

		public:
			//void Update(Vector3 position = VECTOR3_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector3 scale = VECTOR3_ONE);
			void Update() override {};

			// Internal methods
		private:
			bool Init(Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector3 local_scale = VECTOR3_ONE);
			void Release();

			// Static methods
		public:
			static CTransform* Instantiate(Vector2 position);
			static CTransform* Instantiate(Object::UObjectData data = { {} });
			static void Destroy(CTransform *OTranform);

			// Override method
		public:
			void Update(DWORD dt) override;
			void Render() override;
		};
	}
}
