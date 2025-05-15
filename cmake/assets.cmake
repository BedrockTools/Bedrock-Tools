file(GLOB_RECURSE ASSET_FILES "${SRC_ASSETS_DIR}/*")

foreach(asset IN LISTS ASSET_FILES)
    # Skip ignored folders or files
    if(asset MATCHES "/assets/shaders/")
        continue()
    endif()

    # Get relative path
    file(RELATIVE_PATH rel_path "${SRC_ASSETS_DIR}" "${asset}")
    set(dst "${DST_ASSETS_DIR}/${rel_path}")

    # Make directory if needed
    get_filename_component(dst_dir "${dst}" DIRECTORY)
    file(MAKE_DIRECTORY "${dst_dir}")

    # Copy file
    file(COPY "${asset}" DESTINATION "${dst_dir}")
endforeach()