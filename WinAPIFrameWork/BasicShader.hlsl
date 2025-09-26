// 정점 셰이더 입력
struct VS_INPUT {
    float3 pos : POSITION;
};

// 정점 셰이더 출력
struct VS_OUTPUT {
    float4 pos : SV_POSITION;
};

// 버텍스 셰이더
VS_OUTPUT VSMain(VS_INPUT input) {
    VS_OUTPUT output;
    output.pos = float4(input.pos, 1.0f); // 그대로 넘김
    return output;
}

// 픽셀 셰이더
float4 PSMain(VS_OUTPUT input) : SV_TARGET{
    return float4(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색
}
