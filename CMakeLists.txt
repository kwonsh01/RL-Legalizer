cmake_minimum_required(VERSION 3.24)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Python3 REQUIRED COMPONENTS Development)
#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_PATH})
#message(STATUS "PYTHON_INCLUDE_PATH: ${PYTHON_INCLUDE_PATH}")

project(RL_Legalizer)
add_compile_options(-fPIC)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        #src/main.cpp
        src/RLDP.cpp)
set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/submodule/OpenDP/src
        )

set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_SOURCE_DIR}/rldp")
set_source_files_properties(src/rldp.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(src/rldp.i PROPERTIES SWIG_FLAGS "-python")

swig_add_library(RL_Legalizer
        LANGUAGE python
        SOURCES
        src/rldp.i
        ${INCLUDE_DIRS}
        ${SOURCES})

swig_link_libraries(RL_Legalizer
        Python3::Python
        opendplib
        def
        lef)

target_include_directories(RL_Legalizer PRIVATE ${INCLUDE_DIRS})
set_target_properties(RL_Legalizer PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rldp)

add_subdirectory(submodule/OpenDP)

#add_executable(RL_Legalizer ${SOURCES})
#target_include_directories(RL_Legalizer PRIVATE ${INCLUDE_DIRS})
#add_subdirectory(submodule/OpenDP)
#target_link_libraries(RL_Legalizer
#        PRIVATE
#        opendplib
#        def
#        lef)