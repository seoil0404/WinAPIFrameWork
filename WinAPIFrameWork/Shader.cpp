#include "Shader.h"
#include "File.h"
#include "WinGlobal.h"
#include <d3dcompiler.h>

std::map<std::string, Shader*> ShaderManager::shaderData;

Shader* ShaderManager::LoadShader(std::filesystem::path filePath)
{
    if (shaderData.contains(filePath.string()))
        return shaderData[filePath.string()];

    Shader* shader = new Shader;

    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    auto fullPath = (BasePath / filePath);

    // ���ؽ� ���̴� ������
    HRESULT hr = D3DCompileFromFile(
        fullPath.c_str(), nullptr, nullptr,
        "VSMain", "vs_5_0",
        0, 0, &vsBlob, &errorBlob
    );
    if (FAILED(hr)) throw;

    g_device->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        nullptr,
        &shader->vertexShader
    );

    // �ȼ� ���̴� ������
    hr = D3DCompileFromFile(
        fullPath.c_str(), nullptr, nullptr,
        "PSMain", "ps_5_0",
        0, 0, &psBlob, &errorBlob
    );
    if (FAILED(hr)) throw;

    g_device->CreatePixelShader(
        psBlob->GetBufferPointer(),
        psBlob->GetBufferSize(),
        nullptr,
        &shader->pixelShader
    );

    // �Է� ���̾ƿ� (POSITION��)
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    g_device->CreateInputLayout(
        layout, 1,
        vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
        &shader->inputLayout
    );

    vsBlob->Release();
    psBlob->Release();

    shaderData[filePath.string()] = shader;
}
