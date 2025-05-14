CMAKE_MINIMUM_REQUIRED(VERSION 3.5...3.10)
project(imgui)

set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})

if(UNIX)
    target_sources(imgui PRIVATE
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
    )
elseif(WIN32)
    target_sources(imgui PRIVATE
        imgui/backends/imgui_impl_win32.cpp
        imgui/backends/imgui_impl_dx11.cpp
        imgui/backends/imgui_impl_dx12.cpp
    )
endif()

target_link_libraries(imgui PRIVATE d3dcompiler dwmapi)

target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
    $<INSTALL_INTERFACE:include>
)