#pragma once

#include "stdafx.h"
#include "Component.h"

namespace Framework
{
	
	class CCamera : public CComponent
	{
		//Properties
	private:
		Vector2 m_size = { 0,0 };
		float m_angle = 0;
		Vector2 m_scale = { 1,1 };
		Vector3 m_scaleFactors = VECTOR3_ZERO;
		Matrix m_orthographicMatrix = {};
		Matrix m_identityMatrix = {};
		Matrix m_viewMatrix = {};

		// Getter / Setter
	public:
		Matrix &GetOrthographicMatrix() { return m_orthographicMatrix; }
		Matrix &GetIdentityMatrix() { return m_identityMatrix; }
		Matrix &GetViewMatrix() { return m_viewMatrix; }
		Vector2 GetScale() const { return m_scale; }
		Vector2 GetSize() const { return m_size; }

		CCamera* SetScale(const Vector2 &scale);
		CCamera* SetSize(const Vector2 &size);

		// Cons / Des
	public:
		CCamera(const CCamera &camera);
		CCamera(CGameObject* gameObject);
		~CCamera() = default;

		//Override
	public:
		void Update(DWORD dt) override;
		void Render() override;
		CComponent* Clone() override { return new CCamera(*this); }
	};
	
}