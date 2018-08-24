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

#include <csetjmp>

#include <chrono>
#include <iostream>

#include <gsl/gsl>
using namespace gsl;

jmp_buf jb;

template<typename FUNC>
auto benchmark(FUNC func) {
    auto stime = std::chrono::high_resolution_clock::now();
    func();
    auto etime = std::chrono::high_resolution_clock::now();

    return (etime - stime).count();
}

int myfunc1(int val)
{
    if (val >= 0x10000000) {
        return -1;
    }

    if (val < 0x1000) {
        if (auto ret = myfunc1(val + 1); ret == -1) {
            return ret;
        }
    }

    return 0;
}

void myfunc2(int val)
{
    if (val >= 0x10000000) {
        std::longjmp(jb, -1);
    }

    if (val < 0x1000) {
        myfunc2(val + 1);
    }
}

void myfunc3(int val)
{
    if (val >= 0x10000000) {
        throw -1;
    }

    if (val < 0x1000) {
        myfunc3(val + 1);
    }
}

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    if (auto ret = myfunc1(0); ret == 0) {
        std::cout << "myfunc1: success\n";
    }
    else {
        std::cout << "myfunc1: failure\n";
    }

    if (auto ret = myfunc1(0x10000000); ret == 0) {
        std::cout << "myfunc1: success\n";
    }
    else {
        std::cout << "myfunc1: failure\n";
    }

    if (setjmp(jb) == -1) {
        std::cout << "myfunc2: failure\n";
        goto next;
    }

    myfunc2(0);
    std::cout << "myfunc2: success\n";

    myfunc2(0x10000000);
    std::cout << "myfunc2: success\n";

next:

    try {
        myfunc3(0);
        std::cout << "myfunc3: success\n";

        myfunc3(0x10000000);
        std::cout << "myfunc3: success\n";
    }
    catch(...) {
        std::cout << "myfunc3: failure\n";
    }

    uint64_t total1 = 0;
    for (auto i = 0; i < 1000000; i++) {
        total1 += benchmark([&] {
            myfunc1(0);
        });
    }

    uint64_t total2 = 0;
    for (auto i = 0; i < 1000000; i++) {
        total2 += benchmark([&] {
            myfunc2(0);
        });
    }

    uint64_t total3 = 0;
    for (auto i = 0; i < 1000000; i++) {
        total3 += benchmark([&] {
            myfunc3(0);
        });
    }

    std::cout << "time1: " << total1 << '\n';
    std::cout << "time2: " << total2 << '\n';
    std::cout << "time3: " << total3 << '\n';

    return EXIT_SUCCESS;
}

int
main(int argc, char** argv)
{
    try {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}
