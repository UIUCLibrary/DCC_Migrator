cmake_minimum_required(VERSION 3.6)
project(DCC_Migrator)

set(CMAKE_CXX_STANDARD 14)
set(PYTHON_SOURCE
#        src/setup.py
#        src/DCC_pyMigrator/runner.py
        DCC_pyMigrator/__init__.py
        DCC_pyMigrator/__main__.py
        setup.py
        )
#


# TODO: Create test framework for C side

set(DEP_LIBS_FOUND YES)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#####################


# Find deps
find_package(PythonLibs 3 REQUIRED)
find_package(PythonInterp 3 REQUIRED)
find_package(Exiv2 REQUIRED)
find_package(GraphicsMagick COMPONENTS Magick++ REQUIRED)
find_package(Boost COMPONENTS python3 REQUIRED)

# Check deps
if (NOT Boost_PYTHON3_FOUND)

    message(WARNING "Boost python not found")
    set(DEP_LIBS_FOUND NO)
endif ()

if (NOT EXIV2_FOUND)
    message(WARNING "Exiv2 NOT FOUND")
    set(DEP_LIBS_FOUND NO)
endif ()

if (NOT PYTHONLIBS_FOUND)
    message(WARNING "Python NOT FOUND")
    set(DEP_LIBS_FOUND NO)
endif ()

if (NOT PYTHONINTERP_FOUND)
    message(WARNING "Python interp NOT FOUND")
    set(DEP_LIBS_FOUND NO)
endif ()

if (NOT MAGICK++_FOUND)
    message("MAGICK NOT FOUND")
    set(DEP_LIBS_FOUND NO)

endif ()


if (DEP_LIBS_FOUND)
    add_custom_target(RUN_IN_PYTHON
            COMMAND ${PYTHON_EXECUTABLE} DCC_pyMigrator
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS Build_Python_Module
            )
    ADD_CUSTOM_TARGET(Build_Python_Module
            DEPENDS PythonSource exiv2_wrapper)

    add_custom_target(Make_Python_Wheel
            COMMAND ${PYTHON_EXECUTABLE} setup.py bdist_wheel
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
            DEPENDS Build_Python_Module
            )
    add_custom_command(OUTPUT PythonSource
            PRE_BUILD
            BYPRODUCTS ${PYTHON_SOURCE}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/DCC_pyMigrator
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/DCC_pyMigrator ${CMAKE_BINARY_DIR}/DCC_pyMigrator
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/setup.py ${PROJECT_BINARY_DIR}
            COMMENT "Copying Python source to build dir ${PROJECT_BINARY_DIR}/"
            )

#    add_custom_command(
#            PRE_BUILD
#            OUTPUT ${Pyconverted_lib}
#            COMMAND ${PYTHON_EXECUTABLE} setup.py build_ext --inplace
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/DCC_pyMigrator
#            COMMENT "Building PyGraphicsMagick module for Python version ${PYTHONLIBS_VERSION_STRING}"
#            DEPENDS ${CMAKE_BINARY_DIR}/${PYTHON_SOURCE}
#    )
    add_subdirectory(src/)
    #        target_include_directories(src PRIVATE ${PYTHON_INCLUDE_DIR})
else ()
    message(WARNING "Deps not met")
endif ()
