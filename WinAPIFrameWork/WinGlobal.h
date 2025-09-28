#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include "Vector.h"
#include "Scene.h"

// 전역 변수
inline HWND g_hWnd = nullptr;
inline ID3D11Device* g_device = nullptr;
inline ID3D11DeviceContext* g_context = nullptr;
inline IDXGISwapChain* g_swapChain = nullptr;
inline ID3D11RenderTargetView* g_renderTargetView = nullptr;

inline const Vector2 g_viewPort = Vector2((float)(GetSystemMetrics(SM_CXSCREEN)), (float)(GetSystemMetrics(SM_CYSCREEN)));