cmake_minimum_required(VERSION 2.8)
project(EasyML C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

option(BUILD_EXAMPLES "building the examples" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/easyml)

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
