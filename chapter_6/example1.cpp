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

#include <iostream>

#include <gsl/gsl>
using namespace gsl;

void
handle_help()
{
    std::cout
            << "Usage: echo [SHORT-OPTION]... [STRING]...\n"
            << " or: echo LONG-OPTION\n"
            << "Echo the STRING(s) to standard output.\n"
            << "\n"
            << " -n do not output the trailing newline\n"
            << " --help display this help and exit\n"
            << " --version output version information and exit\n";

    ::exit(EXIT_SUCCESS);
}

void
handle_version()
{
    std::cout
            << "echo (example) 1.0\n"
            << "Copyright (C) ???\n"
            << "\n"
            << "Written by Rian Quinn.\n";

    ::exit(EXIT_SUCCESS);
}

int
protected_main(int argc, char **argv)
{
    auto endl = true;
    auto args = make_span(argv, argc);

    for (int i = 1, num = 0; i < argc; i++) {
        cstring_span<> span_arg = ensure_z(args.at(i));

        if (span_arg == "-n") {
            endl = false;
            continue;
        }

        if (span_arg == "--help") {
            handle_help();
        }

        if (span_arg == "--version") {
            handle_version();
        }

        if (num++ > 0) {
            std::cout << " ";
        }

        std::cout << span_arg.data();
    }

    if (endl) {
        std::cout << '\n';
    }

    return EXIT_SUCCESS;
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
