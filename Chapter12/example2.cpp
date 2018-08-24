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

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include <gsl/gsl>
using namespace gsl;

int count = 0;
bool enable_counter = true;

std::mutex mutex;
std::condition_variable cond;

void tick()
{
    cond.notify_one();

    while (enable_counter) {
        count++;
    }
}

template<typename FUNC>
auto timer(FUNC func) {
    std::thread timer{tick};

    std::unique_lock lock(mutex);
    cond.wait(lock);

    func();

    enable_counter = false;
    timer.join();

    return count;
}

int
protected_main(int argc, char** argv)
{
    auto args = make_span(argv, argc);

    if (args.size() != 2) {
        std::cerr << "wrong number of arguments\n";
        ::exit(1);
    }

    auto ticks = timer([&] {
        for (auto i = 0; i < std::stoi(args.at(1)); i++) {
        }
    });

    std::cout << "ticks: " << ticks << '\n';

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
