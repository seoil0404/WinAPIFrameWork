#include "RenderManager.h"
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include "Shader.h"
#include "Vector.h"
#include "WinGlobal.h"

std::array<float, 4> RenderManager::BackgroundColor;
std::vector<DrawCall> RenderManager::drawCalls;

void RenderManager::Draw(
    const Object& object,
	unsigned int indexCount, 
	ID3D11Buffer* vertexBuffer, 
	ID3D11Buffer* indexBuffer, 
	Shader* shader)
{
    DrawCall drawCall(object, indexCount, vertexBuffer, indexBuffer, shader);

    drawCalls.push_back(drawCall);
}

ID3D11Buffer* RenderManager::GetVertexBuffer(Vector3* vertices, unsigned int size)
{
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = sizeof(Vector3) * size;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinitData = {};
    vinitData.pSysMem = vertices;

    ID3D11Buffer* vertexBuffer;

    g_device->CreateBuffer(&vbd, &vinitData, &vertexBuffer);

    return vertexBuffer;
}

ID3D11Buffer* RenderManager::GetIndexBuffer(unsigned int* indices, unsigned int size)
{
    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = sizeof(unsigned int) * size;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinitData = {};
    iinitData.pSysMem = indices;

    ID3D11Buffer* indexBuffer;

    g_device->CreateBuffer(&ibd, &iinitData, &indexBuffer);

    return indexBuffer;
}

void RenderManager::Render()
{
    g_context->ClearRenderTargetView(g_renderTargetView, RenderManager::BackgroundColor.data());
    g_context->ClearDepthStencilView(g_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    UINT stride = sizeof(Vector3);
    UINT offset = 0;

    for (int index = 0; index < drawCalls.size(); index++)
    {
        DrawCall currentDrawCall = drawCalls[index];

        g_context->IASetVertexBuffers(0, 1, &currentDrawCall.vertexBuffer, &stride, &offset);
        g_context->IASetIndexBuffer(currentDrawCall.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        g_context->IASetInputLayout(currentDrawCall.shader->inputLayout);
        g_context->VSSetShader(currentDrawCall.shader->vertexShader, nullptr, (UINT)0);
        g_context->PSSetShader(currentDrawCall.shader->pixelShader, nullptr, (UINT)0);

        ConstantMVPBuffer cb;
        cb.mvp = DirectX::XMMatrixTranspose(RenderManager::GetMVP(currentDrawCall.object));
        g_context->UpdateSubresource(g_constantBuffer, 0, nullptr, &cb, 0, 0);

        g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);

        g_context->DrawIndexed(currentDrawCall.indexCount, 0, 0);
    }

    g_swapChain->Present(1, 0);

    for (int index = 0; index < drawCalls.size(); index++)
    {
        drawCalls[index].indexBuffer->Release();
        drawCalls[index].vertexBuffer->Release();
    }

    drawCalls.clear();
}

DirectX::XMMATRIX RenderManager::GetMVP(const Object& object)
{
    float width = g_viewPort.x;
    float height = g_viewPort.y;

    DirectX::XMMATRIX world = object.GetWorldMatrix();

    DirectX::XMVECTOR eye = XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
    DirectX::XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view = XMMatrixLookAtLH(eye, at, up);

    // 프로젝션 행렬 (원근 투영, 45도 시야각)
    float fovAngleY = XM_PIDIV4; // 45도
    float aspect = width / height;
    float nearZ = 0.1f;
    float farZ = 100.0f;

    DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspect, nearZ, farZ);

    return world * view * projection;
}

DrawCall::DrawCall(
    const Object& object,
    unsigned int indexCount, 
    ID3D11Buffer* vertexBuffer, 
    ID3D11Buffer* indexBuffer, 
    Shader* shader
    ) : object(object), indexCount(indexCount), vertexBuffer(vertexBuffer), indexBuffer(indexBuffer), shader(shader)
{ }