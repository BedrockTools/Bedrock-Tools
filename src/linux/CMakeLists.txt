set(NAME "BedrockTools")
project(${NAME} VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC "./*.cpp")
add_executable(${NAME} ${SRC})

target_link_libraries(${NAME} PRIVATE "BedrockTools.common" webview::core)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${NAME} PRIVATE imgui)
endif()