#pragma once

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Structures.h"
#include "OBJLoader.h"
#include "BaseCamera.h"
#include "GameObject.h"
//#include <wrl.h>

using namespace DirectX;
//using Microsoft::WRL::ComPtr;





struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 DiffuseMaterial;
	XMFLOAT3 LightDir;
	float specPower;
	XMFLOAT4 AmbientLight;
	XMFLOAT4 AmbientMaterial;
	XMFLOAT4 specularLight;
	XMFLOAT4 specularMaterial;
	XMFLOAT3 cameraPosition;

	
	float count;
	unsigned int hasTexture;
};

class DX11Framework
{
	int _WindowWidth = 1280;
	int _WindowHeight = 768;

	ID3D11DeviceContext* _immediateContext = nullptr;
	ID3D11Device* _device;
	IDXGIDevice* _dxgiDevice = nullptr;
	IDXGIFactory2* _dxgiFactory = nullptr;
	ID3D11RenderTargetView* _frameBufferView = nullptr;
	IDXGISwapChain1* _swapChain;
	D3D11_VIEWPORT _viewport;

	ID3D11RasterizerState* _fillState;
	ID3D11RasterizerState* _wireframeState;
	ID3D11RasterizerState* _SkyboxfillState;
	ID3D11VertexShader* _vertexShader;
	ID3D11VertexShader* _vertexShaderSkybox;
	ID3D11InputLayout* _inputLayout;
	ID3D11PixelShader* _pixelShader;
	ID3D11PixelShader* _pixelShaderSkybox;
	ID3D11Buffer* _constantBuffer;
	ID3D11Buffer* _vertexBuffer;
	ID3D11Buffer* _indexBuffer;
	ID3D11Buffer* _pyramidVertexBuffer;
	ID3D11Buffer* _pyramidIndexBuffer;
	ID3D11Buffer* _lineVertexBuffer;
	ID3D11ShaderResourceView* _crateTexture;
	ID3D11ShaderResourceView* _planeTexture;
	ID3D11ShaderResourceView* _skyboxTexture;

	HWND _windowHandle;

	MeshData meshData;

	XMFLOAT4X4 _World;
	XMFLOAT4X4 _World2;
	XMFLOAT4X4 _World3;
	XMFLOAT4X4 _World4;
	XMFLOAT4X4 _World5;
	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection;

	ConstantBuffer _cbData;

	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11SamplerState* _bilinearSamplerState;
	ID3D11DepthStencilState* _depthStencilSkybox;

	XMFLOAT4 _diffuseLight;
	XMFLOAT4 _diffuseMaterial;
	XMFLOAT3 _lightDir;

	XMFLOAT4 _ambientLight;
	XMFLOAT4 _ambientMaterial;

	XMFLOAT4 _specularLight;
	XMFLOAT4 _specularMaterial;
	XMFLOAT3 _cameraPosition;
	
	BaseCamera mainCamera;
	std::vector<BaseCamera> cameras;
	std::vector<GameObject> gameObjects;
	BaseCamera* activeCamera;
	GameObject* activeObject;
	

public:
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nCmdShow);
	HRESULT CreateD3DDevice();
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexIndexBuffers();
	HRESULT InitPipelineVariables();
	HRESULT InitRunTimeData();
	~DX11Framework();
	void Update();
	void Draw();
	int activeCameraIndex = 0;
	int activeObjectIndex = 0;

};

