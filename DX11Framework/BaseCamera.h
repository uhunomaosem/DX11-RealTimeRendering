#pragma once
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <windows.h>
using namespace DirectX;

class BaseCamera
{
private:
	
	
	XMFLOAT3 _at;
	XMFLOAT3 _up;

	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;
	
	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;
	XMFLOAT3 eyeDirection;
	XMFLOAT3 lookAtPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);

public:
	BaseCamera() = default;
	BaseCamera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth);
	~BaseCamera();
	XMFLOAT3 _eye;
	void Update();

	XMFLOAT3 GetAt() { return _at; }
	void SetAt(XMFLOAT3 at) { _at = at; }

	XMFLOAT3 GetPosition() { return _eye; }

	XMMATRIX GetView() 
	{
		return XMLoadFloat4x4(&_view);
	}

	XMMATRIX GetProjection()
	{
		return XMLoadFloat4x4(&_projection);
	}

};