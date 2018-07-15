#
# Copyright (C) 2018 Rian Quinn <rianquinn@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# ------------------------------------------------------------------------------
# Header
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.6)
project(chapter08)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------------------------------------------
# Guideline Support Library
# ------------------------------------------------------------------------------

list(APPEND GSL_CMAKE_ARGS
    -DGSL_TEST=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
)

ExternalProject_Add(
    gsl
    GIT_REPOSITORY https://github.com/Microsoft/GSL.git
    GIT_SHALLOW 1
    CMAKE_ARGS ${GSL_CMAKE_ARGS}
    PREFIX ${CMAKE_BINARY_DIR}/external/gsl/prefix
    TMP_DIR ${CMAKE_BINARY_DIR}/external/gsl/tmp
    STAMP_DIR ${CMAKE_BINARY_DIR}/external/gsl/stamp
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/gsl/download
    SOURCE_DIR ${CMAKE_BINARY_DIR}/external/gsl/src
    BINARY_DIR ${CMAKE_BINARY_DIR}/external/gsl/build
    UPDATE_DISCONNECTED 1
)

# ------------------------------------------------------------------------------
# JSON
# ------------------------------------------------------------------------------

list(APPEND JSON_CMAKE_ARGS
    -DBUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
)

ExternalProject_Add(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_SHALLOW 1
    CMAKE_ARGS ${JSON_CMAKE_ARGS}
    PREFIX ${CMAKE_BINARY_DIR}/external/json/prefix
    TMP_DIR ${CMAKE_BINARY_DIR}/external/json/tmp
    STAMP_DIR ${CMAKE_BINARY_DIR}/external/json/stamp
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/json/download
    SOURCE_DIR ${CMAKE_BINARY_DIR}/external/json/src
    BINARY_DIR ${CMAKE_BINARY_DIR}/external/json/build
    UPDATE_DISCONNECTED 1
)

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------

include_directories(${CMAKE_BINARY_DIR}/include)

add_executable(example1_server example1.cpp)
target_compile_definitions(example1_server PUBLIC SERVER=1)
add_dependencies(example1_server gsl json)

add_executable(example1_client example1.cpp)
target_compile_definitions(example1_client PUBLIC CLIENT=1)
add_dependencies(example1_client gsl json)

add_executable(example2_server example2.cpp)
target_compile_definitions(example2_server PUBLIC SERVER=1)
add_dependencies(example2_server gsl json)

add_executable(example2_client example2.cpp)
target_compile_definitions(example2_client PUBLIC CLIENT=1)
add_dependencies(example2_client gsl json)

add_executable(example3_server example3.cpp)
target_compile_definitions(example3_server PUBLIC SERVER=1)
add_dependencies(example3_server gsl json)

add_executable(example3_client example3.cpp)
target_compile_definitions(example3_client PUBLIC CLIENT=1)
add_dependencies(example3_client gsl json)

add_executable(example4_server example4.cpp)
target_compile_definitions(example4_server PUBLIC SERVER=1)
add_dependencies(example4_server gsl json)

add_executable(example4_client example4.cpp)
target_compile_definitions(example4_client PUBLIC CLIENT=1)
add_dependencies(example4_client gsl json)

add_executable(example5_server example5.cpp)
target_compile_definitions(example5_server PUBLIC SERVER=1)
add_dependencies(example5_server gsl json)

add_executable(example5_client example5.cpp)
target_compile_definitions(example5_client PUBLIC CLIENT=1)
add_dependencies(example5_client gsl json)
