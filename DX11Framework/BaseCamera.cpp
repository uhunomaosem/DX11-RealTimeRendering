#include "BaseCamera.h"



BaseCamera::BaseCamera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth)
{

    _windowHeight = windowHeight;
    _windowWidth = windowWidth;
    _nearDepth = nearDepth;
    _farDepth = farDepth;

    _at = at;
    _up = up;
    _eye = position;
    XMFLOAT3 lookAtPosition(0.0f, 0.0f, 0.0f);
    XMFLOAT3 eyeDirection;
    XMStoreFloat3(&eyeDirection, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&lookAtPosition), XMLoadFloat3(&_eye))));
    //Camera
    float aspect = _windowWidth / _windowHeight;

    XMMATRIX perspective = XMMatrixPerspectiveFovLH(XMConvertToRadians(90), aspect, _nearDepth, _farDepth);
    XMStoreFloat4x4(&_projection, perspective);

    XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&eyeDirection), XMLoadFloat3(&_up)));

}

BaseCamera::~BaseCamera()
{

}

void BaseCamera::Update()
{
    float speed = 3.0f;
    XMFLOAT3 forward(0, 0, 1);
    XMFLOAT3 side(1, 0, 0);
    XMFLOAT3 up(0, 1, 0);
    if (GetAsyncKeyState(0x57) & 0x001)
    {
        //forward
        _eye.x -= forward.x * speed;
        _eye.y -= forward.y * speed;
        _eye.z -= forward.z * speed;

    }
    if (GetAsyncKeyState(0x53) & 0x001)
    {
        //back
        _eye.x += forward.x * speed;
        _eye.y += forward.y * speed;
        _eye.z += forward.z * speed;
    }
    if (GetAsyncKeyState(0x41) & 0x001)
    {
        //right
        _eye.x += side.x * speed;
        _eye.y += side.y * speed;
        _eye.z += side.z * speed;
    }
    if (GetAsyncKeyState(0x44) & 0x001)
    {
        //down
        _eye.x -= side.x * speed;
        _eye.y -= side.y * speed;
        _eye.z -= side.z * speed;
    }

    if (GetAsyncKeyState(0x51) & 0x001)
    {
        //up
        _eye.x -= up.x * speed;
        _eye.y -= up.y * speed;
        _eye.z -= up.z * speed;
    }


    if (GetAsyncKeyState(0x45) & 0x001)
    {
        //left
        _eye.x += up.x * speed;
        _eye.y += up.y * speed;
        _eye.z += up.z * speed;
    }


    float aspect = _windowWidth / _windowHeight;
    XMMATRIX perspective = XMMatrixPerspectiveFovLH(XMConvertToRadians(90), aspect, _nearDepth, _farDepth);
    XMStoreFloat4x4(&_projection, perspective);

    // Recreate view matrix based on the updated _eye position and look direction
    XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&eyeDirection), XMLoadFloat3(&_up)));


}