#TODO: Split extension from straight c functions
set(EXIV2_WRAPPER_SRC boost_migrator_wrapper.cpp metadata.cpp metadata.h)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/DCC_pyMigrator/ext)
if (DEP_LIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIR})
    include_directories(${EXIV2_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    set(Boost_USE_STATIC_LIBS ON)

    PYTHON_ADD_MODULE(exiv2_wrapper ${EXIV2_WRAPPER_SRC})

    target_link_libraries(exiv2_wrapper ${EXIV2_LIBRARY})
    target_link_libraries(exiv2_wrapper ${PYTHON_LIBRARY})
    target_link_libraries(exiv2_wrapper ${Boost_LIBRARIES})
else ()
    message(WARNING "DEP  not found")
endif ()
