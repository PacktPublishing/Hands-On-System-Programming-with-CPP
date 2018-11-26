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

#if SNIPPET01

#include <iostream>

int main(void)
{
    std::cout << "Hello World\n";
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET02

void test(void) {}
void test(bool b) {}

int main(void)
{
    test();
    test(false);
}

// > g++ scratchpad.cpp; ./a.out

#endif

#if SNIPPET03

#include <iostream>

struct mystruct {
    int data1{42};
    int data2{42};
};

int main(void)
{
    mystruct s;
    std::cout << s.data1 << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET04

struct mystruct {
    int data1{};
    int data2{};
    int data3{};
    int data4{};
    int data5{};
    int data6{};
    int data7{};
    int data8{};
};

void test(mystruct *s)
{
}

int main(void)
{
    mystruct s;
    test(&s);
}

// > g++ scratchpad.cpp; ./a.out

#endif

#if SNIPPET05

struct mystruct {
    int data1{};
    int data2{};
    int data3{};
    int data4{};
    int data5{};
    int data6{};
    int data7{};
    int data8{};
};

void test(mystruct &s)
{
}

int main(void)
{
    mystruct s;
    test(s);
}

// > g++ scratchpad.cpp; ./a.out

#endif

#if SNIPPET06

#include <iostream>

int main()
{
    void *ptr;

    if (posix_memalign(&ptr, 0x1000, 42 * sizeof(int))) {
        std::clog << "ERROR: unable to allocate aligned memory\n";
        ::exit(EXIT_FAILURE);
    }

    std::cout << ptr << '\n';
    free(ptr);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55c5d31d1000

#endif

