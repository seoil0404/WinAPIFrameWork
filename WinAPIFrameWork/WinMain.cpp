#include <Windows.h>
#include "WinGlobal.h"
#include <d3d11.h>
#include <dxgi.h>
#include "Shader.h"
#include "Vector.h"
#include "Debug.h"
#include "Scene.h"
#include "Main.h"
#include <string>
#include "RenderManager.h"

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY)
    {
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

    D3D11_BUFFER_DESC cbd = {};
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.ByteWidth = sizeof(ConstantMVPBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    hr = g_device->CreateBuffer(&cbd, nullptr, &g_constantBuffer);
    if (FAILED(hr)) return false;

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = (UINT)g_viewPort.x;   // 화면 크기와 동일
    depthDesc.Height = (UINT)g_viewPort.y;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 깊이24 + 스텐실8
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = g_device->CreateTexture2D(&depthDesc, nullptr, &g_depthStencilBuffer);
    if (FAILED(hr)) return false;

    hr = g_device->CreateDepthStencilView(g_depthStencilBuffer, nullptr, &g_depthStencilView);
    if (FAILED(hr)) return false;

    g_depthStencilBuffer->Release();

    return true;
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
        WS_POPUP,
        0, 0, 
        (int)(g_viewPort.x),
        (int)(g_viewPort.y),
        nullptr, nullptr, hInstance, nullptr
    );

    ShowWindow(g_hWnd, nCmdShow);

    if (!InitD3D(g_hWnd)) return -1;
    Debug::Init();
    System::Awake();

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            System::Update();
            System::Render();
        }
    }

    if (g_renderTargetView) g_renderTargetView->Release();
    if (g_swapChain) g_swapChain->Release();
    if (g_context) g_context->Release();
    if (g_device) g_device->Release();

    return (int)msg.wParam;
}