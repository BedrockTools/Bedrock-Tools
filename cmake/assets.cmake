file(GLOB_RECURSE ASSET_FILES "${SRC_ASSETS_DIR}/*")

foreach(asset IN LISTS ASSET_FILES)
    # Skip ignored folders or files
    if(asset MATCHES "/assets/shaders/")
        continue()
    endif()

    # Get relative path
    file(RELATIVE_PATH RELATIVE "${SRC_ASSETS_DIR}" "${asset}")
    set(OUT "${OUT_ASSETS_DIR}/${RELATIVE}")

    # Make directory if needed
    get_filename_component(OUT_DIR "${OUT}" DIRECTORY)
    file(MAKE_DIRECTORY "${OUT_DIR}")

    # Copy file
    file(COPY "${asset}" DESTINATION "${OUT_DIR}")
endforeach()