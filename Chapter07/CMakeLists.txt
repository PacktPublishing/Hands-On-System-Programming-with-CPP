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
project(chapter07)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------------------------------------------
# Snippets
# ------------------------------------------------------------------------------

function(snippet number)
    add_executable(snippet${number} scratchpad.cpp)
    target_compile_definitions(snippet${number} PRIVATE SNIPPET${number})
    target_link_libraries(snippet${number} rt pthread)
endfunction(snippet)

snippet(01)
snippet(02)
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
snippet(13)
snippet(14)
snippet(15)
snippet(16)
snippet(17)
snippet(18)
snippet(19)
snippet(20)
snippet(21)
snippet(22)
snippet(23)
snippet(24)
snippet(25)
snippet(26)
snippet(27)
snippet(28)
snippet(29)
snippet(30)
snippet(31)
snippet(32)
snippet(33)
snippet(34)
snippet(35)
snippet(36)
snippet(37)
snippet(38)
snippet(39)
snippet(40)
snippet(41)
snippet(42)
snippet(43)
snippet(44)
snippet(45)
snippet(46)
snippet(47)
snippet(48)
snippet(49)
snippet(50)
snippet(51)
snippet(52)
snippet(53)
snippet(54)
snippet(55)
snippet(56)
snippet(57)
snippet(58)
