#pragma once

#include "Header.h"
#include <DirectXMath.h>
#include "Component.h"

namespace Framework {

	class CCamera : public CComponent
	{
		//Properties
	private:
		int _width;
		int _height;
		float _angle;
		Vector3 _scaleFactors;
		Matrix _orthographicMatrix;
		Matrix _identityMatrix;
		Matrix _viewMatrix;

		// Getter / Setter
	public:
		Matrix &GetOrthographicMatrix() { return _orthographicMatrix; }
		Matrix &GetIdentityMatrix() { return _identityMatrix; }
		Matrix &GetViewMatrix() { return _viewMatrix; }

		// Cons / Des
	public:
		CCamera(CGameObject* gameObject);
		CCamera(CGameObject* gameObject, int width, int height, float angle, Vector3 scaleFactors);
		~CCamera();

		//Override
	public:
		void Update(DWORD dt) override;
		void Render() override;
	};

}