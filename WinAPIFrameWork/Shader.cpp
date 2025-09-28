#include "Shader.h"
#include "File.h"
#include "WinGlobal.h"
#include <d3dcompiler.h>

void ShaderManager::SetBasicShader(std::filesystem::path filePath)
{
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    auto fullPath = (BasePath / filePath);
    
    // 버텍스 셰이더 컴파일
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
        &g_BasicShader.vertexShader
    );

    // 픽셀 셰이더 컴파일
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
        &g_BasicShader.pixelShader
    );

    // 입력 레이아웃 (POSITION만)
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    g_device->CreateInputLayout(
        layout, 1,
        vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
        &g_BasicShader.inputLayout
    );

    vsBlob->Release();
    psBlob->Release();
}