set(EXIV2_WRAPPER_SRC
        reader.cpp
        reader.h
        ImageMetadata.cpp
        ImageMetadata.h
        Exiv2Wrapper.h)

set(pyEXIV2_WRAPPER_SRC boost_exiv2_wrapper.cpp)

if (DEP_LIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIR})

    include_directories(${EXIV2_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    set(Boost_USE_STATIC_LIBS ON)
    add_library(Exiv_wrapper ${EXIV2_WRAPPER_SRC})
    PYTHON_ADD_MODULE(pyExiv2 ${pyEXIV2_WRAPPER_SRC})

    target_link_libraries(Exiv_wrapper ${EXIV2_LIBRARY})

    target_link_libraries(pyExiv2 ${Boost_LIBRARIES})
    target_link_libraries(pyExiv2 ${PYTHON_LIBRARY})
    target_link_libraries(pyExiv2 Exiv_wrapper)
else ()
    message(WARNING "DEP  not found")
endif ()
