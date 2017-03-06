if (NOT LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/DCC_pyMigrator/ext)
endif ()

add_subdirectory(Exiv2Wrapper)
add_subdirectory(MagickWrapper)