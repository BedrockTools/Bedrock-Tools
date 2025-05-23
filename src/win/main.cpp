//#include <windows.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "src/common/AppUI.hpp"
#if DEBUG_BUILD
    #include <imgui/imgui.h>
    #include <imgui/backends/imgui_impl_dx11.h>
    #include <imgui/backends/imgui_impl_win32.h>
#endif

#include <webview/webview.h>

#include "src/common/rendering/DirectX11.hpp"
#include "src/common/MainWindow.hpp"
inline MainWindow g_MainWindow{};

static LRESULT CALLBACK WebViewProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
        default:
            return webview::browser_engine::window_proc_handler(hWnd, iMsg, wParam, lParam);

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        {
            bool isFocused = iMsg == WM_SETFOCUS;
            break;
        };

        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            std::cout << "Meow!" << std::endl;
            /*switch (wParam)
            {
                case VK_F11:
                {
                    if (iMsg != WM_KEYDOWN)
                        break;

                    std::cout << "Meow!" << std::endl;
                    g_MainWindow.setFullScreen(!g_MainWindow.isFullScreen());
                    break;
                };
            };*/

            break;
        };
    };

    return 0;
};

static LRESULT CALLBACK WidgetProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
        default:
            return webview::browser_engine::widget_proc_handler(hWnd, iMsg, wParam, lParam);

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        {
            bool isFocused = iMsg == WM_SETFOCUS;
            break;
        };

        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            std::cout << "Meow!" << std::endl;
            break;
        };
    };

    return 0;
};


#if DEBUG_BUILD
static void DebugWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, bool* bIsDone);
#endif

LPCTSTR g_WindowClassName = TEXT("Bedrock Tools");
LPCTSTR g_DebugClassName = TEXT("Bedrock Tools - Debug");
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char* appData = std::getenv("APPDATA");
    const char* localAppData = std::getenv("LOCALAPPDATA");
    if (appData)
    {
        std::filesystem::path appFolder = std::filesystem::path(appData) / "com.xkingdark.bedrocktools";
        if (!std::filesystem::exists(appFolder))
            std::filesystem::create_directories(appFolder);

        Logger::s_File.open(appFolder / "Bedrock-Tools.log");
        Logger::s_bShouldFormat = false;

        Logger::log(Logger::LogLevel::Debug,
            std::format("AppData path: {}", appFolder.string()));
    };

    bool bIsDone = false;

#if DEBUG_BUILD
    std::thread([&hInstance, &hPrevInstance, &bIsDone] {
        DebugWindow(hInstance, hPrevInstance, &bIsDone);
    }).detach();
#endif

    std::thread([] {
        AppUI::serveHttp();
    }).detach();

    webview::webview::set_data_path(std::format("{}\\com.xkingdark.bedrocktools", localAppData));
    webview::webview::set_window_style(WS_POPUPWINDOW);
    try {
        g_MainWindow.initialize(std::make_shared<webview::webview>(
            true, nullptr, false,
            WebViewProc, WidgetProc
        ), 800, 600);

        //void* pWidget = g_MainWindow.getWebview()->widget().value();
        void* pWindow = g_MainWindow.getWebview()->window().value();
        while (!bIsDone)
        {
            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    bIsDone = true;
                    goto _cleanup;
                    //return (int)msg.wParam;
                }
                else {
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                };
            };

            auto hWnd = static_cast<HWND>(pWindow);
        #if DEBUG_BUILD
            SetWindowTextA(hWnd, g_MainWindow.getWindowTitle().c_str());
        #endif

            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            g_MainWindow.update(width, height);
        };
    }
    catch (const webview::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    };

_cleanup:
    bIsDone = true;
    g_MainWindow.terminate();

    std::cout << "Quit correctly." << std::endl;
    return 0;
};

#if DEBUG_BUILD
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, iMsg, wParam, lParam))
        return true;

    switch (iMsg)
    {
        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_SIZE:
        {
            if (wParam != SIZE_MINIMIZED)
            {
                g_ResizeWidth = static_cast<UINT>(LOWORD(lParam));
                g_ResizeHeight = static_cast<UINT>(HIWORD(lParam));
            };
            break;
        };

        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        {
            bool isFocused = iMsg == WM_SETFOCUS;
            break;
        };

        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            std::cout << "Meow!" << std::endl;
            break;
        };

        case WM_DESTROY:
            PostQuitMessage(0); break;
    };

    return 0;
};

static void DebugWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, bool* bIsDone)
{
    // Debug window
    if (!hPrevInstance)
    {
        WNDCLASS wc{ 0 };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
        wc.lpszClassName = g_DebugClassName;
        RegisterClass(&wc);
    };

    ImGui_ImplWin32_EnableDpiAwareness();

    HWND hWnd = CreateWindow(
        g_DebugClassName,
        g_DebugClassName,

        WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, /* position */
        350, 550, /* size */
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    // Initialize Direct3D
    if (!CreateDeviceD3D(hWnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(g_DebugClassName, hInstance);
        return;
    };

    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);

    // ImGui Setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);


    while (!*bIsDone)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                goto _cleanup;
                //return (int)msg.wParam;
            }
            else {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            };
        };

        // Handle window being minimized or screen locked
        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        };

        ImGui_ImplWin32_NewFrame();
        ImGui_ImplDX11_NewFrame();
        ImGui::NewFrame();
        {
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("Settings"))
                {
                    if (ImGui::MenuItem("Fullscreen", "F11", g_MainWindow.isFullScreen()))
                    {
                        g_MainWindow.setFullScreen(!g_MainWindow.isFullScreen());
                    };

                    if (ImGui::MenuItem("V-Sync", "", g_MainWindow.isVsyncEnabled()))
                    {
                        g_MainWindow.setVsyncEnabled(!g_MainWindow.isVsyncEnabled());
                    };

                    if (ImGui::MenuItem("Crash Client"))
                    {
                        std::cout << "Meow!~" << std::endl;
                        const auto a = reinterpret_cast<volatile int*>(0xDEADC0DE);
                        *a = 1;
                    };

                    if (ImGui::MenuItem("Open Console"))
                    {
                        // Debug console
                        AllocConsole();
                        FILE* ostream; freopen_s(&ostream, "CONOUT$", "w", stdout);
                        //FILE* istream; freopen_s(&istream, "CONIN$", "r", stdin);
                        SetConsoleTitle(g_DebugClassName);
                    };

                    ImGui::EndMenu();
                };

                ImGui::Text("Frame Time: %.1f ms", 1000.0f / io.Framerate);
                ImGui::Text(std::format("- Renderer: {}", (int)bgfx::getRendererType()).c_str());

                ImGui::EndMainMenuBar();
            };
        };

        // Rendering
        ImGui::Render();

        static auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        const float clear_color_with_alpha[4] = {
            clear_color.x * clear_color.w,
            clear_color.y * clear_color.w,
            clear_color.z * clear_color.w,
            clear_color.w
        };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Present
        const HRESULT hr = g_pSwapChain->Present(g_MainWindow.isVsyncEnabled(), 0);
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    };

_cleanup:
    *bIsDone = true;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();

    ::DestroyWindow(hWnd);
    ::UnregisterClass(g_DebugClassName, hInstance);
};
#endif