if (WIN32)
    set(PLATFORM windows)
    set(PROFILE s_5_0)
elseif (UNIX AND NOT APPLE)
    set(PLATFORM linux)
    set(PROFILE 440)
elseif (APPLE)  # macOS
    set(PLATFORM darwin)
    set(PROFILE metal)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

message(STATUS "PLATFORM: ${PLATFORM}")
message(STATUS "PROFILE: ${PROFILE}")

function(compile_shader SHADER_PATH SHADER_TYPE)
    get_filename_component(SHADER_NAME "${SHADER_PATH}" NAME_WE)
    get_filename_component(SHADER_DIR "${SHADER_PATH}" DIRECTORY)

    file(RELATIVE_PATH SHADER_SUBDIR "${SRC_ASSETS_DIR}/shaders" "${SHADER_DIR}")
    set(OUTPUT_PATH "${OUT_ASSETS_DIR}/shaders/${SHADER_SUBDIR}/${SHADER_SUBDIR}.${SHADER_TYPE}.bin")

    # Make directory if needed
    get_filename_component(OUT_DIR "${OUTPUT_PATH}" DIRECTORY)
    file(MAKE_DIRECTORY "${OUT_DIR}")

    execute_process(COMMAND ${SOURCE_DIR}/tools/${PLATFORM}/shaderc
        -f ${SHADER_PATH}
        -o ${OUTPUT_PATH}
        --type ${SHADER_TYPE}
        --varyingdef ${SHADER_DIR}/varying.def.sc
        -i ${SOURCE_DIR}/src-deps/bgfx/bgfx/src
        --profile ${PROFILE}
        --platform ${PLATFORM}
        RESULT_VARIABLE result
    )

    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Shaderc failed for ${SHADER_PATH}")
    endif()
endfunction()

# Find all shaders
file(GLOB_RECURSE VERTEX_SHADERS "${SRC_ASSETS_DIR}/shaders/*/vertex.sc")
file(GLOB_RECURSE FRAGMENT_SHADERS "${SRC_ASSETS_DIR}/shaders/*/fragment.sc")

foreach(vs IN LISTS VERTEX_SHADERS)
    compile_shader(${vs} vertex)
endforeach()

foreach(fs IN LISTS FRAGMENT_SHADERS)
    compile_shader(${fs} fragment)
endforeach()