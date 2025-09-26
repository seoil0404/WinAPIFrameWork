#include <Windows.h>
#include "Main.h"
#include <d3d11.h>
#include <dxgi.h>
#include "Shader.h"
#include "Vector.h"
#include "Debug.h"
#include "Scene.h"

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Direct3D 초기화
bool InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        &g_swapChain,
        &g_device,
        nullptr,
        &g_context
    );

    if (FAILED(hr)) return false;

    ID3D11Texture2D* backBuffer = nullptr;
    g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    g_device->CreateRenderTargetView(backBuffer, nullptr, &g_renderTargetView);
    g_context->OMSetRenderTargets(1, &g_renderTargetView, nullptr);
    D3D11_VIEWPORT vp = {};
    vp.Width = g_viewPort.x;   // 창 너비
    vp.Height = g_viewPort.y;   // 창 높이
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_context->RSSetViewports(1, &vp);
    backBuffer->Release();

    return true;
}

TriangleScene* triangle;

// 렌더링
void Render()
{
    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 검은색
    g_context->ClearRenderTargetView(g_renderTargetView, clearColor);

    UINT stride = sizeof(Vector3);
    UINT offset = 0;

    ID3D11Buffer* vertexBuffer = triangle->GetVertexBuffer();
    ID3D11Buffer* indexBuffer = triangle->GetIndexBuffer();
    
    g_context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    g_context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    g_context->IASetInputLayout(g_BasicShader.inputLayout);
    g_context->VSSetShader(g_BasicShader.vertexShader, nullptr, 0);
    g_context->PSSetShader(g_BasicShader.pixelShader, nullptr, 0);

    g_context->DrawIndexed(3, 0, 0);

    g_swapChain->Present(1, 0);

    Debug::Log("Rendered");
}

// WinMain
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DXWindowClass";
    RegisterClassEx(&wc);

    g_hWnd = CreateWindowEx(
        0,
        L"DXWindowClass",
        L"DirectX Black Screen",
        WS_OVERLAPPEDWINDOW,
        100, 100, g_viewPort.x, g_viewPort.y,
        nullptr, nullptr, hInstance, nullptr
    );

    ShowWindow(g_hWnd, nCmdShow);

    if (!InitD3D(g_hWnd)) return -1;

    Debug::Init();

    ShaderManager::SetBasicShader("BasicShader.hlsl");

    triangle = new TriangleScene();

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            Render();
        }
    }

    if (g_renderTargetView) g_renderTargetView->Release();
    if (g_swapChain) g_swapChain->Release();
    if (g_context) g_context->Release();
    if (g_device) g_device->Release();

    return (int)msg.wParam;
}