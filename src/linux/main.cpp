#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "src/common/MainWindow.hpp"
#include <webview/webview.h>

inline MainWindow g_MainWindow{};

int main(int argc, char* argv[])
{
    bool bIsDone = false;

    std::thread([] {
        AppUI::serveHttp();
    }).detach();

    webview::webview webView{ true, nullptr };

    void* pWidget = webView.widget().value();
    void* pWindow = webView.window().value();

    try
    {
        webView.set_title("Bedrock Tools");
        webView.set_size(800, 600, WEBVIEW_HINT_MIN);
        webView.set_size(800, 600, WEBVIEW_HINT_NONE);

        webView.navigate("http://127.0.0.1:56729/index.html");

        g_MainWindow.initialize(pWindow, 800, 600);
        while (!bIsDone)
        {
            int width = 800;
            int height = 600;
            g_MainWindow.update(width, height);
        };
    }
    catch (const webview::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    };

_cleanup:
    bIsDone = true;

    MainWindow::terminate();
    webView.terminate();

    std::cout << "Quit correctly." << std::endl;
    return 0;
};