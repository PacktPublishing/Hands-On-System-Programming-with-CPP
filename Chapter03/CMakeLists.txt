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
project(chapter03)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------------------------------------------
# Snippets
# ------------------------------------------------------------------------------

function(snippet number)
    add_executable(snippet${number} scratchpad.cpp)
    target_compile_definitions(snippet${number} PRIVATE SNIPPET${number})
endfunction(snippet)

snippet(00)
snippet(00a)
snippet(00b)
snippet(01)
snippet(01a)
snippet(02)
snippet(02a)
snippet(03)
snippet(04)
snippet(05)
snippet(06)
snippet(07)
snippet(08)
snippet(09)
snippet(10)
snippet(11)
snippet(12)
snippet(12a)
snippet(13)
snippet(14)
snippet(15)
snippet(16)
snippet(17)
snippet(18)
snippet(19)
snippet(20)
snippet(21)
