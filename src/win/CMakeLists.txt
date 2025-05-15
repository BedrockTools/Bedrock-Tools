set(NAME "BedrockTools")
project(${NAME} VERSION ${PROJECT_VERSION})

include("assets/resources.cmake")

file(GLOB_RECURSE SRC "./*.cpp")
add_executable(${NAME} WIN32 ${SRC} ${SHARED_SOURCES})

target_link_libraries(${NAME} PRIVATE d3d11 d3d12 "BedrockTools.common" webview::core)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${NAME} PRIVATE imgui)
endif()