cmake_minimum_required(VERSION 3.24)
find_package(SWIG REQUIRED)

project(RL_Legalizer)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        src/main.cpp
        src/RLDP.cpp)
set(INCLUDE_DIRS
        #${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/submodule/OpenDP/src
        )
add_executable(RL_Legalizer ${SOURCES})
target_include_directories(RL_Legalizer PRIVATE ${INCLUDE_DIRS})
add_subdirectory(submodule/OpenDP)
target_link_libraries(RL_Legalizer PRIVATE opendplib def lef)