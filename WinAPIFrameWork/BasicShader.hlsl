// ���� ���̴� �Է�
struct VS_INPUT {
    float3 pos : POSITION;
};

// ���� ���̴� ���
struct VS_OUTPUT {
    float4 pos : SV_POSITION;
};

// ���ؽ� ���̴�
VS_OUTPUT VSMain(VS_INPUT input) {
    VS_OUTPUT output;
    output.pos = float4(input.pos, 1.0f); // �״�� �ѱ�
    return output;
}

// �ȼ� ���̴�
float4 PSMain(VS_OUTPUT input) : SV_TARGET{
    return float4(1.0f, 0.0f, 0.0f, 1.0f); // ������
}
