#pragma once

#include "stdafx.h"
#include "Component.h"

namespace Framework
{
	
	class CCamera : public CComponent
	{
		//Properties
	private:
		int m_width = 0;
		int m_height = 0;
		float m_angle = 0;
		Vector3 m_scaleFactors = VECTOR3_ZERO;
		Matrix m_orthographicMatrix = {};
		Matrix m_identityMatrix = {};
		Matrix m_viewMatrix = {};

		// Getter / Setter
	public:
		Matrix &GetOrthographicMatrix() { return m_orthographicMatrix; }
		Matrix &GetIdentityMatrix() { return m_identityMatrix; }
		Matrix &GetViewMatrix() { return m_viewMatrix; }

		// Cons / Des
	public:
		CCamera(const CCamera &camera);
		CCamera(CGameObject* gameObject);
		CCamera(CGameObject* gameObject, int width, int height, float angle, Vector3 scaleFactors);
		~CCamera() = default;

		//Override
	public:
		void Update(DWORD dt) override;
		void Render() override;

		CCamera* Clone() const override;
	};
	
}