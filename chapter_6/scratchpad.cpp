//
// Copyright (C) 2018 Rian Quinn <rianquinn@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// -----------------------------------------------------------------------------
// Section: Stream Based IO
// -----------------------------------------------------------------------------

#if SNIPPET01

#include <iostream>

int main()
{
    std::cout << "Hello World\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET02

#include <iostream>

int main()
{
    std::cout << "The answer is: " << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET03

#include <iostream>

int main()
{
    auto n = 0;

    std::cin >> n;
    std::cout << "input: " << n << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42 ↵
// input: 42

#endif

#if SNIPPET04

#include <fcntl.h>
#include <string.h>
#include <iostream>

class custom_errno
{ };

std::ostream &operator<<(std::ostream &os, const custom_errno &e)
{ return os << strerror(errno); }

int main()
{
    if (open("filename.txt", O_RDWR) == -1) {
        std::cout << custom_errno{} << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// No such file or directory

#endif

#if SNIPPET05

#include <iostream>

struct object_t
{
    int data1;
    int data2;
};

std::ostream &operator<<(std::ostream &os, const object_t &obj)
{
    os << "data1: " << obj.data1 << '\n';
    os << "data2: " << obj.data2 << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, object_t &obj)
{
    is >> obj.data1;
    is >> obj.data2;
    return is;
}

int main()
{
    object_t obj;

    std::cin >> obj;
    std::cout << obj;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42 ↵
// 43 ↵
// data1: 42
// data2: 43

#endif

#if SNIPPET06

#include <stdio.h>

int main()
{
    char buf[2];
    scanf("%s", buf);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is 42 ↵
// *** stack smashing detected ***: <unknown> terminated
// Aborted (core dumped)

#endif

#if SNIPPET07

#include <stdio.h>

int main()
{
    char buf[2];
    scanf("%2s", buf);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is 42 ↵

#endif

#if SNIPPET08

#include <iomanip>
#include <iostream>

template<std::size_t N>
class buf_t
{
    char m_buf[N];

public:

    constexpr auto size()
    { return N; }

    constexpr auto data()
    { return m_buf; }
};

template<std::size_t N>
std::istream &operator>>(std::istream &is, buf_t<N> &b)
{
    is >> std::setw(b.size()) >> b.data();
    return is;
}

int main()
{
    buf_t<2> buf;
    std::cin >> buf;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is 42 ↵

#endif

#if SNIPPET09

#include <string>
#include <iostream>

int main()
{
    std::string buf;
    std::cin >> buf;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is 42 ↵

#endif

#if SNIPPET10

#include <iostream>

int main()
{
    std::cout << "buffered" << '\n';
    std::cout << "buffer flushed" << std::endl;
    std::cerr << "buffer flushed" << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// buffer
// buffer flushed
// buffer flushed

#endif

#if SNIPPET11

#include <iostream>

#ifndef NDEBUG
#define DEBUG(...) fprintf(stdout, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

int main()
{
    DEBUG("The answer is: %d\n", 42);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET12

#include <iostream>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#ifndef NDEBUG
#define DEBUG(level,...) \
    if(level <= DEBUG_LEVEL) fprintf(stdout, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

int main()
{
    DEBUG(0, "The answer is: %d\n", 42);
    DEBUG(1, "The answer no is: %d\n", 43);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET13

#include <iostream>

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

int main()
{
    if constexpr (!g_ndebug) {
        std::cout << "The answer is: " << 42 << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET14

#include <iostream>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

int main()
{
    if constexpr (!g_ndebug && (0 <= g_debug_level)) {
        std::cout << "The answer is: " << 42 << '\n';
    }

    if constexpr (!g_ndebug && (1 <= g_debug_level)) {
        std::cout << "The answer is not: " << 43 << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET15

#include <iostream>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

template <std::size_t LEVEL>
constexpr void debug(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        func();
    };
}

int main()
{
    debug<0>([] {
        std::cout << "The answer is: " << 42 << '\n';
    });

    debug<1>([] {
        std::cout << "The answer is not: " << 43 << '\n';
    });
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET16

#include <iostream>

#ifndef NDEBUG
#define DEBUG(fmt, args...) \
    fprintf(stdout, "%s [%d]: " fmt, __FILE__, __LINE__, args);
#else
#define DEBUG(...)
#endif

int main()
{
    DEBUG("The answer is: %d\n", 42);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// scratchpad.cpp [11]: The answer is: 42

#endif

#if SNIPPET17

#include <iostream>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

#define console std::cout << __FILE__ << " [" << __LINE__ << "]: "

template <std::size_t LEVEL>
constexpr void debug(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        func();
    };
}

int main()
{
    debug<0>([] {
        console << "The answer is: " << 42 << '\n';
    });
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// scratchpad.cpp [27]: The answer is: 42

#endif

#if SNIPPET18

#include <iostream>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

#define console std::cout << __FILE__ << " [" << __LINE__ << "]: "

template <std::size_t LEVEL>
constexpr void debug(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        std::cout << "\033[1;32mDEBUG\033[0m ";
        func();
    };
}

template <std::size_t LEVEL>
constexpr void warning(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        std::cout << "\033[1;33mWARNING\033[0m ";
        func();
    };
}

template <std::size_t LEVEL>
constexpr void fatal(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        std::cout << "\033[1;31mFATAL ERROR\033[0m ";
        func();
        ::exit(-1);
    };
}

template <std::size_t LEVEL>
constexpr void fatal(int error_code, void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        std::cout << "\033[1;31mFATAL ERROR\033[0m ";
        func();
        ::exit(error_code);
    };
}

int main()
{
    debug<0>([] {
        console << "The answer is: " << 42 << '\n';
    });

    warning<0>([] {
        console << "The answer might be: " << 42 << '\n';
    });

    fatal<0>([] {
        console << "The answer was not: " << 42 << '\n';
    });
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// DEBUG scratchpad.cpp [54]: The answer is: 42
// WARNING scratchpad.cpp [58]: The answer might be: 42
// FATAL ERROR scratchpad.cpp [62]: The answer was not: 42

#endif

#if SNIPPET19

#include <sstream>
#include <iostream>

int main()
{
    std::stringstream stream;
    stream << "The answer is: " << 42 << '\n';

    std::cout << stream.str() << std::flush;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET20

#include <iostream>

int main()
{
    std::clog << "The answer is: " << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42

#endif

// -----------------------------------------------------------------------------
// Section: Manipulators
// -----------------------------------------------------------------------------

#if SNIPPET21

#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET22

#include <iostream>

int main()
{
    std::cout << "Hello World\n" << std::flush;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET23

#include <iostream>

int main()
{
    std::cout << "Hello World\n";
    std::cout << "Hello World\n";
    std::cout << "Hello World\n";
    std::cout << "Hello World" << std::endl;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Hello World
// Hello World
// Hello World
// Hello World

#endif

#if SNIPPET24

#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
    std::cout << "Hello World" << std::endl;
    std::cout << "Hello World" << std::endl;
    std::cout << "Hello World" << std::endl;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Hello World
// Hello World
// Hello World
// Hello World

#endif

#if SNIPPET25

#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    std::cout << "The answer is: " << true << '\n';
    std::cout << "The answer is: " << false << '\n';

    std::cout << std::noboolalpha;
    std::cout << "The answer is: " << true << '\n';
    std::cout << "The answer is: " << false << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: true
// The answer is: false
// The answer is: 1
// The answer is: 0

#endif

#if SNIPPET26

#include <iostream>

int main()
{
    std::cout << "The answer is: " << 42 << '\n' << std::hex
              << "The answer is: " << 42 << '\n';
    std::cout << "The answer is: " << 42 << '\n' << std::dec
              << "The answer is: " << 42 << '\n';
    std::cout << "The answer is: " << 42 << '\n' << std::oct
              << "The answer is: " << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 42
// The answer is: 2a
// The answer is: 2a
// The answer is: 42
// The answer is: 42
// The answer is: 52

#endif

#if SNIPPET27

#include <iostream>

int main()
{
    std::cout << std::hex << std::uppercase << "The answer is: "
              << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 2A

#endif

#if SNIPPET28

#include <iostream>

int main()
{
    std::cout << std::showbase;
    std::cout << std::hex << "The answer is: " << 42 << '\n';
    std::cout << std::dec << "The answer is: " << 42 << '\n';
    std::cout << std::oct << "The answer is: " << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 0x2a
// The answer is: 42
// The answer is: 052

#endif

#if SNIPPET29

#include <iostream>

int main()
{
    int i = 0;
    std::cout << &i << '\n';
    std::cout << std::hex << std::showbase << std::uppercase
              << reinterpret_cast<uintptr_t>(&i) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7fff51d370b4
// 0X7FFF51D370B4

#endif

#if SNIPPET30

#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "The answer is: " << std::setw(18) << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is:                 42

#endif

#if SNIPPET31

#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "The answer is: " << std::setw(18) << std::setfill('0')
              << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 000000000000000042

#endif

#if SNIPPET32

#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "The answer is: "
              << std::setw(18) << std::left << std::setfill('0')
              << 42 << '\n';

    std::cout << "The answer is: "
              << std::setw(18) << std::right << std::setfill('0')
              << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 420000000000000000
// The answer is: 000000000000000042

#endif

#if SNIPPET33

#include <iomanip>
#include <iostream>

int main()
{
    int i = 0;

    std::cout << std::hex
              << std::showbase;

    std::cout << "The answer is: "
              << std::setw(18) << std::internal << std::setfill('0')
              << 42 << '\n';

    std::cout << "The answer is: "
              << std::setw(18) << std::internal << std::setfill('0')
              << &i << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 0x000000000000002a
// The answer is: 0x00007ffc074c9be4

#endif

#if SNIPPET34

#include <iostream>

int main()
{
    auto flags = std::cout.flags();
    std::cout.flags(flags);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out

#endif

#if SNIPPET35

#include <iomanip>
#include <iostream>

template<typename FUNC>
void cout_transaction(FUNC f)
{
    auto flags = std::cout.flags();
    f();
    std::cout.flags(flags);
}

int main()
{
    cout_transaction([]{
        std::cout << std::hex << std::showbase;
        std::cout << "The answer is: " << 42 << '\n';
    });

    std::cout << "The answer is: " << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 0x2a
// The answer is: 42

#endif

#if SNIPPET36

#include <iomanip>
#include <iostream>

namespace usr
{
    class hex_t { } hex;
}

std::ostream &
operator<<(std::ostream &os, const usr::hex_t &obj)
{
    os << std::hex << std::showbase << std::internal
        << std::setfill('0') << std::setw(18);

    return os;
}

int main()
{
    std::cout << "The answer is: " << usr::hex << 42 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// The answer is: 0x000000000000002a

#endif
