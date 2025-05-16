#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <sstream>
#include <string>
#include <format>
#include <iostream>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/platform.h>

#include "AppUI.hpp"

class MainWindow
{
private:
    int m_Width = 800;
    int m_Height = 600;
    bool m_Vsync = false;
    bool m_FullScreen = false;

public:
    void initialize(void*, int, int);
    void update(int, int);
    static void terminate();

    std::string getWindowTitle() const;

    bool isFullScreen() const { return this->m_FullScreen; };
    void setFullScreen(bool fullscreen) { this->m_FullScreen = fullscreen; };

    bool isVsyncEnabled() const { return this->m_Vsync; };
    void setVsyncEnabled(bool vsync) { this->m_Vsync = vsync; };
};

#endif // !MAINWINDOW_HPP