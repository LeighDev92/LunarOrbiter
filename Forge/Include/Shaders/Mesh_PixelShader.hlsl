Texture2D diffuseTexture : register(t0);
SamplerState textureSampler : register(s0);

struct PointLight
{
    float3 position;
    float padding;

    float3 color;
    float intensity;

    float radius;
    float3 padding2;
};

struct VertexShaderOutput
{
    float4 position         : SV_POSITION;
    float2 uv               : TEXCOORD;
    float3 world_position   : WORLD_POSITION;
    float3 normal           : NORMAL;
    float4 color            : COLOR;
};

cbuffer MaterialConstantBuffer : register(b1)
{
	float4 diffuseColor;
	bool hasTexture;
	bool hasDisplacement;
	float displacementStrength;
    bool isLit;
};

cbuffer LightingConstantBuffer : register(b2)
{
    float3 camera_position;
    float padding_lighting;

    PointLight point_lights[8];

    int num_point_lights;
    float3 padding_lighting2;
};

float3 diffuse(PointLight light, float3 world_position, float3 normal, float diffuse_reflection_coefficient)
{
    float3 light_direction = normalize(light.position - world_position);
    float diffuse = diffuse_reflection_coefficient * max(dot(normal, light_direction), 0.0f);
    float distance_to_light = length(light.position - world_position);
    float attenuation = saturate(1.0f - distance_to_light / max(light.radius, 0.0001f));
    attenuation *= attenuation;

    return light.color * light.intensity * diffuse * attenuation;
}

float4 main(VertexShaderOutput input) : SV_TARGET
{
    float4 texture_color = diffuseColor;

    if(hasTexture)
    {
        texture_color = diffuseTexture.Sample(textureSampler,input.uv);
    }

    float3 lighting = float3(1.f, 1.f, 1.f);

    if(isLit)
    {
        float3 normal = normalize(input.normal);
        
        float3 ambient = float3(0.05f, 0.05f, 0.05f);
        lighting = ambient;

        for (int i = 0; i < num_point_lights; i++)
        {
            lighting += diffuse(point_lights[i], input.world_position, normal, 1.0f);
        }
    }
    
    float3 final_color = texture_color.rgb * input.color.rgb * lighting;

    return float4(final_color, texture_color.a * input.color.a);
}