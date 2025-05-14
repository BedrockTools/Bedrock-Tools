cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(NAME "BedrockTools")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(${NAME} LANGUAGES CXX VERSION 1.0.0)

# Git info
set(GIT_BRANCH "main")
set(GIT_SHA "unknown")
set(GIT_COMMIT_COUNT "0")
set(GIT_COMMIT_TIME "0")

find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND git branch --show-current
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    execute_process(
        COMMAND git rev-parse --verify HEAD
        OUTPUT_VARIABLE GIT_SHA
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    execute_process(
        COMMAND git rev-list --count HEAD
        OUTPUT_VARIABLE GIT_COMMIT_COUNT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    execute_process(
        COMMAND git show -s --format=%ct
        OUTPUT_VARIABLE GIT_COMMIT_TIME
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endif()

message(STATUS "GIT_BRANCH is '${GIT_BRANCH}'")
message(STATUS "GIT_SHA is '${GIT_SHA}'")
message(STATUS "GIT_COMMIT_TIME is '${GIT_COMMIT_TIME}'")

add_compile_definitions(
    BUILD_TYPE="${CMAKE_BUILD_TYPE}"
    GIT_BRANCH="${GIT_BRANCH}"
    GIT_SHA="${GIT_SHA}"
    GIT_COMMIT_COUNT="${GIT_COMMIT_COUNT}"
    GIT_COMMIT_TIME="${GIT_COMMIT_TIME}"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_BUILD=1)
else()
    add_compile_definitions(DEBUG_BUILD=0)
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /Zc:preprocessor")
endif()

# Dependencies
include_directories("${CMAKE_SOURCE_DIR}/src-deps")

#Webview
add_subdirectory("${CMAKE_SOURCE_DIR}/src-deps/webview")
include_directories("${CMAKE_SOURCE_DIR}/src-deps/webview/core/include")

#bgfx stuff
include_directories("${CMAKE_SOURCE_DIR}/src-deps/bgfx/bgfx/include")
include_directories("${CMAKE_SOURCE_DIR}/src-deps/bgfx/bimg/include")
include_directories("${CMAKE_SOURCE_DIR}/src-deps/bgfx/bx/include")

set (BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set (BGFX_CUSTOM_TARGETS OFF CACHE BOOL "" FORCE)
set (BGFX_INSTALL OFF CACHE BOOL "" FORCE)
add_compile_definitions(BX_CONFIG_DEBUG=0)
add_subdirectory("${CMAKE_SOURCE_DIR}/src-deps/bgfx")


set(COPYRIGHT "Copyright 2025, xKingDark")
set(VENDOR "xKingDark")
set(DESCRIPTION "Bedrock Tools")
set(SHARED_SOURCES)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include(assets/platform/macos/resources.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(assets/platform/windows/resources.cmake)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Main executable.
file(GLOB_RECURSE SRC "./src/*.cpp")
add_executable(${NAME} MACOSX_BUNDLE WIN32)
target_sources(${NAME} PRIVATE ${SRC} ${SHARED_SOURCES})
target_link_libraries(${NAME} PRIVATE bgfx webview::core)

#imgui
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory("${CMAKE_SOURCE_DIR}/src-deps/imgui")
    include_directories("${CMAKE_SOURCE_DIR}/src-deps/imgui")
    target_link_libraries(${NAME} PRIVATE imgui)
endif()

if (WIN32)
    target_link_libraries(${NAME} PRIVATE d3d11 d3d12)
endif()

set(SRC_ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(DST_ASSETS_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
        -DSRC_ASSETS_DIR=${SRC_ASSETS_DIR}
        -DDST_ASSETS_DIR=${DST_ASSETS_DIR}
        -P ${CMAKE_SOURCE_DIR}/cmake/assets.cmake
        -P ${CMAKE_SOURCE_DIR}/cmake/shaders.cmake
    COMMENT "Copying assets"
)