#ifndef DIRECTX11_HPP
#define DIRECTX11_HPP

#ifdef _WIN32

#include <d3d11.h>
#include <tchar.h>

// Data
inline ID3D11Device*           g_pd3dDevice = nullptr;
inline ID3D11DeviceContext*    g_pd3dDeviceContext = nullptr;
inline IDXGISwapChain*         g_pSwapChain = nullptr;
inline bool                    g_SwapChainOccluded = false;
inline UINT                    g_ResizeWidth = 0, g_ResizeHeight = 0;
inline ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

#endif

#endif // !DIRECTX11_HPP
