cmake_minimum_required(VERSION 3.6)
project(DCC_Migrator)

set(CMAKE_CXX_STANDARD 11)
set(PYTHON_SOURCE
        DCC_pyMigrator/setup.py
        DCC_pyMigrator/runner.py
        DCC_pyMigrator/__init__.py
        DCC_pyMigrator/__main__.py
        )

#TODO: Split extension from straight c functions
set(PYTHON_EXTENSION_SOURCE
        DCC_pyMigrator/src/migrate.cpp
        DCC_pyMigrator/src/convert.cpp
        DCC_pyMigrator/src/convert.h
        DCC_pyMigrator/src/metadata.cpp
        DCC_pyMigrator/src/metadata.h

        )

# TODO: Create test framework for C side

set(DEP_LIBS_FOUND YES)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#####################
set(Pyconverted_lib ${CMAKE_CURRENT_BINARY_DIR}/pygmagick.cpython-36m-darwin.so)


# Find deps
find_package(PythonLibs 3 REQUIRED)
find_package(PythonInterp 3 REQUIRED)
find_package(Exiv2 REQUIRED)
find_package(GraphicsMagick COMPONENTS Magick++ REQUIRED)

# Check deps
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
    include_directories(${PYTHON_INCLUDE_DIR})
    include_directories(${EXIV2_INCLUDE_DIR})
    include_directories(${MAGICK_INCLUDE_DIR})

    add_custom_target(helloWorld
            COMMAND ${PYTHON_EXECUTABLE} runner.py
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/DCC_pyMigrator
            DEPENDS ${PYTHON_SOURCE} ${Pyconverted_lib}
            )

    add_custom_command(OUTPUT DCC_pyMigrator
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/DCC_pyMigrator/
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_command(OUTPUT ${PYTHON_SOURCE}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory DCC_pyMigrator ${CMAKE_BINARY_DIR}/DCC_pyMigrator
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Copying Python source to build dir"
            DEPENDS DCC_pyMigrator
            )
    add_custom_command(
            PRE_BUILD
            OUTPUT ${Pyconverted_lib}
            COMMAND ${PYTHON_EXECUTABLE} setup.py build_ext --inplace
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/DCC_pyMigrator
            COMMENT "Building PyGraphicsMagick module for Python version ${PYTHONLIBS_VERSION_STRING}"
            DEPENDS ${CMAKE_BINARY_DIR}/${PYTHON_SOURCE}
    )
    add_library(_ SHARED ${CMAKE_CURRENT_SOURCE_DIR}/${PYTHON_EXTENSION_SOURCE})
    #        target_include_directories(DCC_pyMigrator PRIVATE ${PYTHON_INCLUDE_DIR})
else ()
    message(WARNING "Deps not met")
endif ()
