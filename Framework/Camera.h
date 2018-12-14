#pragma once

#include "stdafx.h"
#include "Component.h"

namespace Framework
{
	
	class CCamera : public CComponent
	{
		//Properties
	private:
		int _width = 0;
		int _height = 0;
		float _angle = 0;
		Vector3 _scaleFactors = VECTOR3_ZERO;
		Matrix _orthographicMatrix = {};
		Matrix _identityMatrix = {};
		Matrix _viewMatrix = {};

		// Getter / Setter
	public:
		Matrix &GetOrthographicMatrix() { return _orthographicMatrix; }
		Matrix &GetIdentityMatrix() { return _identityMatrix; }
		Matrix &GetViewMatrix() { return _viewMatrix; }

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