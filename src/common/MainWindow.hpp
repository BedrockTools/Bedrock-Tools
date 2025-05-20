#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <sstream>
#include <string>
#include <format>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/platform.h>
#include <webview/webview.h>

class MainWindow
{
private:
    int m_Width = 800;
    int m_Height = 600;
    bool m_Vsync = false;
    bool m_FullScreen = false;
    std::shared_ptr<webview::webview> m_Webview;

public:
    void initialize(const std::shared_ptr<webview::webview>&, int, int);
    void update(int, int);
    void terminate() const;

    std::string getWindowTitle() const;

    bool isFullScreen() const { return this->m_FullScreen; };
    void setFullScreen(bool fullscreen) { this->m_FullScreen = fullscreen; };

    const std::shared_ptr<webview::webview>& getWebview() const { return m_Webview; };

    bool isVsyncEnabled() const { return this->m_Vsync; };
    void setVsyncEnabled(bool vsync) { this->m_Vsync = vsync; };
};

#endif // !MAINWINDOW_HPP