set(NAME "BedrockTools.common")
project(${NAME} VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC "./*.cpp" "./*.hpp")
add_library(${NAME} ${SRC})
target_link_libraries(${NAME} PRIVATE bgfx)

# Copying assets
set(SRC_ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
set(DST_ASSETS_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMENT "Copying assets"
    COMMAND ${CMAKE_COMMAND}
    -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
    -DSRC_ASSETS_DIR=${SRC_ASSETS_DIR}
    -DDST_ASSETS_DIR=${DST_ASSETS_DIR}
    -P ${CMAKE_SOURCE_DIR}/cmake/assets.cmake
    -P ${CMAKE_SOURCE_DIR}/cmake/shaders.cmake
)