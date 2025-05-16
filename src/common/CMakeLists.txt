set(NAME "BedrockTools.common")
project(${NAME} VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC "./*.cpp" "./*.hpp")
add_library(${NAME} ${SRC})
target_link_libraries(${NAME} PRIVATE bgfx http-server)

# Copying assets
set(SRC_ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(OUT_ASSETS_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
    -DSRC_ASSETS_DIR=${SRC_ASSETS_DIR}
    -DOUT_ASSETS_DIR=${OUT_ASSETS_DIR}
    -P ${CMAKE_SOURCE_DIR}/cmake/shaders.cmake
    -P ${CMAKE_SOURCE_DIR}/cmake/assets.cmake
    COMMENT "Copying assets"
)

# Building UI
set(UI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src-ui")
set(UI_BUILD_DIR "${UI_SOURCE_DIR}/dist")
set(UI_OUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data/ui")

add_custom_command(
    TARGET ${NAME} PRE_BUILD
    COMMAND bun run build
    WORKING_DIRECTORY ${UI_SOURCE_DIR}
    COMMENT "Building UI with bun"
)

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${UI_OUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${UI_BUILD_DIR} ${UI_OUT_DIR}
    COMMENT "Copying built UI to ${UI_OUT_DIR}"
)