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

#include <fstream>
#include <iostream>

#include <gsl/gsl>
using namespace gsl;

void
redirect_output(
    const std::ifstream &is,
    const std::ofstream &os,
    std::function<void()> f)
{
    auto cinrdbuf = std::cin.rdbuf();
    auto coutrdbuf = std::cout.rdbuf();

    std::cin.rdbuf(is.rdbuf());
    std::cout.rdbuf(os.rdbuf());

    f();

    std::cin.rdbuf(cinrdbuf);
    std::cout.rdbuf(coutrdbuf);
}

auto
open_streams(cstring_span<> port)
{
    std::ifstream is(port.data());
    std::ofstream os(port.data());

    if (!is || !os) {
        std::clog << "ERROR: unable to open serial port:" << port.data() << '\n';
        ::exit(EXIT_FAILURE);
    }

    return std::make_pair(std::move(is), std::move(os));
}

int
protected_main(int argc, char** argv)
{
    auto args = make_span(argv, argc);

    if (argc != 2) {
        std::clog << "ERROR: unsupported number of arguments\n";
        ::exit(EXIT_FAILURE);
    }

    auto [is, os] = open_streams(
        ensure_z(args.at(1))
    );

    redirect_output(is, os, []{
        std::string buf;

        std::cin >> buf;
        std::cout << buf << std::flush;
    });

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
