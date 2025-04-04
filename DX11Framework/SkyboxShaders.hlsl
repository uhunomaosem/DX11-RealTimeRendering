cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
    float4 DiffuseLight;
    float4 DiffuseMaterial;
    float3 LightDir;
    float specPower;
    float4 AmbientLight;
    float4 AmbientMaterial;
    float4 specularLight;
    float4 specularMaterial;
    float3 cameraPosition;

    
    float count;
    uint hasTexture;
}

TextureCube skybox : register(t0);
SamplerState bilinearSampler : register(s0);

struct SkyBoxVS_Out
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

SkyBoxVS_Out VS_SkyBox(float3 Position : POSITION, float3 Normal : NORMAL, float2 texCoord : TEXCOORD)
{
    SkyBoxVS_Out output = (SkyBoxVS_Out)0;
    

    float4 Pos4 = float4(Position, 1.0f);
    output.position = mul(Pos4, World);

    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.position = output.position.xyww;
    output.texCoord = Position;
    return output;
    
}


float4 PS_SkyBox(SkyBoxVS_Out output) : SV_TARGET
{
    return skybox.Sample(bilinearSampler, output.texCoord);
}