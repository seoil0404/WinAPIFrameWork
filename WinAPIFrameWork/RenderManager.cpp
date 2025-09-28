#include "RenderManager.h"
#include <d3d11.h>
#include <dxgi.h>
#include "Shader.h"
#include "Vector.h"
#include "WinGlobal.h"

std::array<float, 4> RenderManager::BackgroundColor;
std::vector<DrawCall> RenderManager::drawCalls;

void RenderManager::Draw(
	unsigned int indexCount, 
	ID3D11Buffer* vertexBuffer, 
	ID3D11Buffer* indexBuffer, 
	Shader* shader)
{
    DrawCall drawCall;
    drawCall.indexCount = indexCount;
    drawCall.vertexBuffer = vertexBuffer;
    drawCall.indexBuffer = indexBuffer;
    drawCall.shader = shader;

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
    UINT stride = sizeof(Vector3);
    UINT offset = 0;

    for (int index = 0; index < drawCalls.size(); index++)
    {
        DrawCall currentDrawCall = drawCalls[index];

        g_context->IASetVertexBuffers(0, 1, &currentDrawCall.vertexBuffer, &stride, &offset);
        g_context->IASetIndexBuffer(currentDrawCall.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        g_context->IASetInputLayout(currentDrawCall.shader->inputLayout);
        g_context->VSSetShader(currentDrawCall.shader->vertexShader, nullptr, 0);
        g_context->PSSetShader(currentDrawCall.shader->pixelShader, nullptr, 0);

        g_context->DrawIndexed(currentDrawCall.indexCount, 0, 0);
    }

    drawCalls.clear();
}