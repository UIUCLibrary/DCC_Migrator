include_directories(${PROJECT_SOURCE_DIR}/src/Exiv2Wrapper)
add_executable(Test_Exiv2 catch.hpp test_exiv2_wrapper.cpp)
add_custom_command(TARGET
        Test_Exiv2
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
        BYPRODUCTS data/00000003.tif data/00000003_editable.tif
        COMMENT "Copying test files to build folder"
        )
target_link_libraries(Test_Exiv2 Exiv_wrapper)