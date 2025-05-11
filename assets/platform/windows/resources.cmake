configure_file("${CMAKE_CURRENT_LIST_DIR}/version.rc.in" "assets/platform/windows/version.rc" @ONLY)
list(APPEND SHARED_SOURCES
    "assets/platform/windows/resources.rc"
    "${CMAKE_CURRENT_BINARY_DIR}/assets/platform/windows/version.rc")