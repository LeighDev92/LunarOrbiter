Texture2D displacementMap : register(t1);
SamplerState textureSampler : register(s0);

struct VertexShaderInput
{
    float3 position : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD;
    float4 color    : COLOR;
};

struct VertexShaderOutput
{
    float4 position         : SV_POSITION;
    float2 uv               : TEXCOORD;
    float3 world_position   : WORLD_POSITION;
    float3 normal           : NORMAL;
    float4 color            : COLOR;
};

cbuffer model_constant_buffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

cbuffer MaterialConstantBuffer : register(b1)
{
	float4 diffuseColor;
	bool hasTexture;
	bool hasDisplacement;
	float displacementStrength;
    bool isLit;
};

VertexShaderOutput main(VertexShaderInput input)
{
    if (hasDisplacement)
    {
        float height = displacementMap.SampleLevel(textureSampler, input.uv, 0).r;
        float displacement = (height - 0.5f) * displacementStrength;
        input.position = input.position + input.normal * displacement;
    }

    float4 local_position = float4(input.position, 1.f);
    float4 world_position = mul(local_position, model);

    VertexShaderOutput output;
    output.position = mul(mul(world_position, view), projection);
    output.world_position = world_position.xyz;
    output.normal = normalize(mul(input.normal, (float3x3)model));
    output.uv = input.uv;
    output.color = input.color;

    return output;
}