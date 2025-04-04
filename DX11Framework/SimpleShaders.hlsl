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

Texture2D diffuseTex : register(t0);
SamplerState bilinearSampler : register(s0);



struct VS_Out
{
    float4 position : SV_POSITION;
    float3 worldNormal : NORMAL;
    float4 color : COLOR;
    float3 PosW : POSITION0;
    float2 texCoord : TEXCOORD;
};



VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 texCoord : TEXCOORD)
{   
    VS_Out output = (VS_Out)0;
    
    float4 Pos4 = float4(Position, 1.0f);
    output.position = mul(Pos4, World);
    output.PosW = output.position;
    
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.worldNormal = mul(float4(Normal, 0), World);
    
    output.texCoord = texCoord;

    
    return output;
}



float4 PS_main(VS_Out output) : SV_TARGET
{
    float4 texColor = diffuseTex.Sample(bilinearSampler, output.texCoord);

    float3 lightDir = -LightDir;
    float3 worldNormal = normalize(output.worldNormal);
    float3 viewDir = normalize(cameraPosition - output.PosW);

    float NdotL = saturate(dot(worldNormal, normalize(lightDir)));

    float4 SpecularColor;
    float4 DiffuseColor = NdotL * DiffuseLight * DiffuseMaterial;
    
    if (hasTexture == 1)
    {
        DiffuseColor = texColor * NdotL;
    }
    float3 halfVec = normalize(lightDir + viewDir);
    float spec = pow(saturate(dot(worldNormal, halfVec)), specPower);
    SpecularColor = spec * specularLight * specularMaterial;
    
 
    
    float4 finalColor = texColor * (DiffuseColor + SpecularColor);
    output.color = finalColor;
    return finalColor;
}