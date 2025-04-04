#pragma once

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "OBJLoader.h"
#include "json.hpp"


using json = nlohmann::json;

class GameObject
{
private:
	ID3D11ShaderResourceView* texture = nullptr;
	MeshData meshData;
	DirectX::XMFLOAT4X4 world;

public:
	GameObject() = default;



	void SetShaderResource(ID3D11ShaderResourceView* in) { texture = in; }
	void SetMeshData(MeshData in) { meshData = in; }

	ID3D11ShaderResourceView** GetShaderResource() { return &texture; }
	MeshData* GetMeshData() {return &meshData;}
};

