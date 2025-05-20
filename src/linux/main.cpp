#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "src/common/MainWindow.hpp"

inline MainWindow g_MainWindow{};
int main(int argc, char* argv[])
{
    bool bIsDone = false;

    std::thread([] {
        AppUI::serveHttp();
    }).detach();

    try {
        g_MainWindow.initialize(
            std::make_shared<webview::webview>(true, nullptr),
            800, 600);

        //void* pWidget = g_MainWindow.getWebview()->widget().value();
        void* pWindow = g_MainWindow.getWebview()->window().value();
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
    g_MainWindow.terminate();

    std::cout << "Quit correctly." << std::endl;
    return 0;
};