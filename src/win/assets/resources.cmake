configure_file("assets/version.rc.in" "assets/platform/windows/version.rc" @ONLY)
list(APPEND SHARED_SOURCES
    "assets/resources.rc"
    "${CMAKE_CURRENT_BINARY_DIR}/assets/platform/windows/version.rc")