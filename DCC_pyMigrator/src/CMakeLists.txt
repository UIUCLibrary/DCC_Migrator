#TODO: Split extension from straight c functions
set(runner_src runner.cpp)
set(BOOST_MIGRATOR_SRC boost_migrator_wrapper.cpp metadata.cpp metadata.h)

if (DEP_LIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIR})
    include_directories(${EXIV2_INCLUDE_DIR})
    include_directories(${MAGICK_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    set(Boost_USE_STATIC_LIBS ON)

    PYTHON_ADD_MODULE(dcc_migrator ${BOOST_MIGRATOR_SRC})

    target_link_libraries(dcc_migrator ${EXIV2_LIBRARY})
    target_link_libraries(dcc_migrator ${MAGICK++_LIBRARIES})
    target_link_libraries(dcc_migrator ${PYTHON_LIBRARY})
    target_link_libraries(dcc_migrator ${Boost_LIBRARIES})
else ()
    message(WARNING "DEP  not found")
endif ()
