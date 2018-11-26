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
project(book)

include(ExternalProject)

# ------------------------------------------------------------------------------
# Helper
# ------------------------------------------------------------------------------

function(add_chapter name)
    ExternalProject_Add(
        ${name}
        PREFIX ${CMAKE_BINARY_DIR}/extras/${name}/prefix
        TMP_DIR ${CMAKE_BINARY_DIR}/extras/${name}/tmp
        STAMP_DIR ${CMAKE_BINARY_DIR}/extras/${name}/stamp
        DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/extras/${name}/download
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/${name}
        BINARY_DIR ${CMAKE_BINARY_DIR}/extras/${name}/build
        INSTALL_COMMAND ""
    )
endfunction(add_chapter)

# ------------------------------------------------------------------------------
# Chapters
# ------------------------------------------------------------------------------

add_chapter(Chapter02)
add_chapter(Chapter03)
add_chapter(Chapter04)
add_chapter(Chapter05)
add_chapter(Chapter06)
add_chapter(Chapter07)
add_chapter(Chapter08)
add_chapter(Chapter09)
add_chapter(Chapter10)
add_chapter(Chapter11)
add_chapter(Chapter12)
add_chapter(Chapter13)
