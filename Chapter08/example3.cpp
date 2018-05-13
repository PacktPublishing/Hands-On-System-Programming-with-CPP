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

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <chrono>
#include <fstream>
#include <iostream>

constexpr auto size = 0x1000;

template<typename FUNC>
auto benchmark(FUNC func) {
    auto stime = std::chrono::high_resolution_clock::now();
    func();
    auto etime = std::chrono::high_resolution_clock::now();

    return etime - stime;
}

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    using namespace std::chrono;

    {
        char buf[size] = {};
        if (auto file = std::fstream("test.txt", std::ios::out)) {
            file.write(buf, size);
        }
    }

    {
        char buf[size];
        if (auto file = std::fstream("test.txt", std::ios::in)) {
            auto time = benchmark([&file, &buf]{
                file.read(buf, size);
            });

            std::cout << "c++ time: "
                      << duration_cast<microseconds>(time).count()
                      << '\n';
        }
    }

    {
        void *buf;
        if (int fd = open("test.txt", O_RDONLY); fd != 0) {
            auto time = benchmark([&fd, &buf]{
                buf = mmap(NULL, size, PROT_READ, 0, fd, 0);
            });

            munmap(buf, size);

            std::cout << "mmap time: "
                      << duration_cast<microseconds>(time).count()
                      << '\n';
        }
    }

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
