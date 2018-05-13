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

#include <unistd.h>

#include <fstream>
#include <iostream>

#include <gsl/gsl>
using namespace gsl;

constexpr auto mode = std::ios::in | std::ios::ate;

[[noreturn]] void
tail(std::fstream &file)
{
    while (true) {
        file.peek();
        while(!file.eof()) {
            auto pos = file.tellg();

            std::string buf;
            std::getline(file, buf, '\n');

            if (file.eof() && !file.good()) {
                file.seekg(pos);
                break;
            }

            std::cout << buf << '\n';
        }

        sleep(1);

        file.clear();
        file.sync();
    }
}

int
protected_main(int argc, char **argv)
{
    std::string filename;
    auto args = make_span(argv, argc);

    if (args.size() < 2) {
        std::cin >> filename;
    }
    else {
        filename = ensure_z(args[1]).data();
    }

    if (auto file = std::fstream(filename, mode)) {
        tail(file);
    }

    throw std::runtime_error("failed to open file");
}

int
main(int argc, char **argv)
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
