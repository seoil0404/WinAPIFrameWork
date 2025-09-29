cbuffer ConstantBuffer : register(b0)
{
    matrix mvp;
};

struct VS_INPUT
{
    float3 pos : POSITION;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
};

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    return float4(1, 1, 1, 1);
}

PS_INPUT VSMain(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = mul(float4(input.pos, 1.0f), mvp);
    return output;
}