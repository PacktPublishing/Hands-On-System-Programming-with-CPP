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

#include <list>
#include <mutex>
#include <thread>
#include <iostream>
#include <algorithm>

#include <gsl/gsl>
using namespace gsl;

using namespace std::string_literals;

class primes
{
    std::list<int> m_primes;
    mutable std::mutex m_mutex;

public:

    void add(int prime)
    {
        std::unique_lock lock(m_mutex);
        m_primes.push_back(prime);
    }

    void print()
    {
        std::unique_lock lock(m_mutex);
        m_primes.sort();

        for (const auto prime : m_primes) {
            std::cout << prime << ' ';
        }

        std::cout << '\n';
    }
};

primes g_primes;

void check_prime(int num)
{
    for (auto i = 2; i < num; i++) {
        if (num % i == 0) {
            return;
        }
    }

    g_primes.add(num);
}

int
protected_main(int argc, char** argv)
{
    auto args = make_span(argv, argc);

    if (args.size() != 4) {
        std::cerr << "wrong number of arguments\n";
        ::exit(1);
    }

    int max_prime = std::stoi(args.at(1));
    int max_threads = std::stoi(args.at(2));

    if (max_prime < 3) {
        std::cerr << "max_prime must be 2 or more\n";
        ::exit(1);
    }

    if (max_threads < 1) {
        std::cerr << "max_threads must be 1 or more\n";
        ::exit(1);
    }

    for (auto i = 2; i < max_prime; i += max_threads) {

        std::list<std::thread> threads;
        for (auto t = 0; t < max_threads; t++) {
            threads.push_back(std::thread{check_prime, i + t});
        }

        for (auto &thread : threads) {
            thread.join();
        }
    }

    if (args.at(3) == "print"s) {
        g_primes.print();
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
