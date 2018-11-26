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

int main(void)
{
    if (auto i = 42; i > 0) {
        std::cout << "Hello World\n";
    }
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET02

#include <iostream>

int main(void)
{
    switch(auto i = 42) {
        case 42:
            std::cout << "Hello World\n";
            break;

        default:
            break;
    }
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET03

#include <iostream>

constexpr const auto val = true;

int main(void)
{
    if (val) {
        std::cout << "Hello World\n";
    }
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET04

#include <iostream>

int main(void)
{
    if constexpr (constexpr const auto i = 42; i > 0) {
        std::cout << "Hello World\n";
    }
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET05

#include <iostream>

int main(void)
{
    static_assert(42 == 42, "the answer");
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET06

#include <iostream>

int main(void)
{
    static_assert(42 == 42);
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET07

#include <iostream>

namespace X::Y::Z
{
    auto msg = "Hello World\n";
}

int main(void)
{
    std::cout << X::Y::Z::msg;
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET08

#include <iostream>

namespace X
{
namespace Y
{
namespace Z
{
    auto msg = "Hello World\n";
}
}
}

int main(void)
{
    std::cout << X::Y::Z::msg;
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET09

#include <iostream>

std::pair<const char *, int>
give_me_a_pair()
{
    return {"The answer is: ", 42};
}

int main(void)
{
    auto [msg, answer] = give_me_a_pair();
    std::cout << msg << answer << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET10

#include <utility>
#include <iostream>

std::pair<const char *, int>
give_me_a_pair()
{
    return {"The answer is: ", 42};
}

int main(void)
{
    auto p = give_me_a_pair();
    std::cout << std::get<0>(p) << std::get<1>(p) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET11

#include <iostream>

struct mystruct
{
    const char *msg;
    int answer;
};

mystruct
give_me_a_struct()
{
    return {"The answer is: ", 42};
}

int main(void)
{
    auto [msg, answer] = give_me_a_struct();
    std::cout << msg << answer << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET12

#include <iostream>

inline auto msg = "Hello World\n";

int main(void)
{
    std::cout << msg;
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET13

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World\n");
    std::cout << str;
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET14

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World");

    std::cout << str.front() << '\n';
    std::cout << str.back() << '\n';
    std::cout << str.at(1) << '\n';
    std::cout << str.data() << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// H
// d
// e
// Hello World

#endif

#if SNIPPET15

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World");

    std::cout << str.size() << '\n';
    std::cout << str.max_size() << '\n';
    std::cout << str.empty() << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 11
// 4611686018427387899
// 0

#endif

#if SNIPPET16

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World");

    str.remove_prefix(1);
    str.remove_suffix(1);
    std::cout << str << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// ello Worl

#endif

#if SNIPPET17

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World");
    std::cout << str.substr(0, 5) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// Hello

#endif

#if SNIPPET18

#include <iostream>
#include <string_view>

int main(void)
{
    std::string_view str("Hello World");

    if (str.compare("Hello World") == 0) {
        std::cout << "Hello World\n";
    }

    std::cout << str.compare("Hello") << '\n';
    std::cout << str.compare("World") << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// Hello World
// 6
// -1

#endif

#if SNIPPET19

#include <iostream>

int main(void)
{
    std::string_view str("Hello this is a test of Hello World");

    std::cout << str.find("Hello") << '\n';
    std::cout << str.rfind("Hello") << '\n';
    std::cout << str.find_first_of("Hello") << '\n';
    std::cout << str.find_last_of("Hello") << '\n';
    std::cout << str.find_first_not_of("Hello") << '\n';
    std::cout << str.find_last_not_of("Hello") << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 0
// 24
// 0
// 33
// 5
// 34

#endif

#if SNIPPET20

#include <iostream>
#include <any>

struct mystruct {
    int data;
};

int main(void)
{
    auto myany = std::make_any<int>(42);
    std::cout << std::any_cast<int>(myany) << '\n';

    myany = 4.2;
    std::cout << std::any_cast<double>(myany) << '\n';

    myany = mystruct{42};
    std::cout << std::any_cast<mystruct>(myany).data << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 42
// 4.2
// 42

#endif

#if SNIPPET21

#include <iostream>
#include <variant>

int main(void)
{
    std::variant<int, double> v = 42;
    std::cout << std::get<int>(v) << '\n';

    v = 4.2;
    std::cout << std::get<double>(v) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 42
// 4.2

#endif

#if SNIPPET22

#include <iostream>
#include <optional>

class myclass
{
public:
    int val;

    myclass(int v) :
        val{v}
    {
        std::cout << "constructed\n";
    }
};

int main(void)
{
    std::optional<myclass> o;
    std::cout << "created, but not constructed\n";

    if (o) {
        std::cout << "Attempt #1: " << o->val << '\n';
    }

    o = myclass{42};

    if (o) {
        std::cout << "Attempt #2: " << o->val << '\n';
    }
}

// > g++ scratchpad.cpp; ./a.out
// created, but not constructed
// constructed
// Attempt #2: 42

#endif

#if SNIPPET23

#include <iostream>

class myclass
{
public:
    myclass()
    {
        std::cout << "Hello from constructor\n";
    }

    ~myclass()
    {
        std::cout << "Hello from destructor\n";
    }
};

int main(void)
{
    myclass c;
}

// > g++ scratchpad.cpp; ./a.out
// Hello from constructor
// Hello from destructor

#endif

#if SNIPPET24

#include <iostream>

class myclass
{
    int *ptr;

public:
    myclass() :
        ptr{new int(42)}
    { }

    ~myclass()
    {
        delete ptr;
    }

    int get()
    {
        return *ptr;
    }
};

int main(void)
{
    myclass c;
    std::cout << "The answer is: " << c.get() << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// The answer is: 42

#endif

#if SNIPPET25

#include <iostream>

class myclass
{
    FILE *m_file;

public:
    myclass(const char *filename) :
        m_file{fopen(filename, "rb")}
    {
        if (m_file == 0) {
            throw std::runtime_error("unable to open file");
        }
    }

    ~myclass()
    {
        fclose(m_file);
        std::clog << "Hello from destructor\n";
    }
};

int main(void)
{
    myclass c1("test.txt");

    try {
        myclass c2("does_not_exist.txt");
    }
    catch(const std::exception &e) {
        std::cout << "exception: " << e.what() << '\n';
    }
}

// > g++ scratchpad.cpp; touch test.txt; ./a.out
// exception: unable to open file
// Hello from destructor

#endif

#if SNIPPET26

#include <gsl/gsl>

void init(int *p)
{
    *p = 0;
}

int main(void)
{
    auto p = new int;
    init(p);
    delete p;
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET27

#include <gsl/gsl>

void init(int *p)
{
    *p = 0;
}

int main(void)
{
    gsl::owner<int *> p = new int;
    init(p);
    delete p;
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET28

#include <gsl/gsl>

gsl::not_null<int *>
test(gsl::not_null<int *> p)
{
    return p;
}

int main(void)
{
    auto p1 = std::make_unique<int>();
    auto p2 = test(gsl::not_null(p1.get()));
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET29

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

int main(void)
{
    int array[5] = {1, 2, 3, 4, 5};
    auto span = gsl::span(array);

    for (const auto &elem : span) {
        std::clog << elem << '\n';
    }

    for (auto i = 0; i < 5; i++) {
        std::clog << span[i] << '\n';
    }

    try {
        std::clog << span[5] << '\n';
    }
    catch(const gsl::fail_fast &e) {
        std::cout << "exception: " << e.what() << '\n';
    }
}

// > g++ scratchpad.cpp; ./a.out
// 1
// 2
// 3
// 4
// 5
// 1
// 2
// 3
// 4
// 5
// exception: GSL: Precondition failure at ...

#endif

#if SNIPPET30

#include <gsl/gsl>
#include <iostream>

int main(void)
{
    gsl::cstring_span<> str = gsl::ensure_z("Hello World\n");
    std::cout << str.data();

    for (const auto &elem : str) {
        std::clog << elem;
    }
}

// > g++ scratchpad.cpp; ./a.out
// Hello World
// Hello World

#endif

#if SNIPPET31

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

int main(void)
{
    try {
        Expects(false);
    }
    catch(const gsl::fail_fast &e) {
        std::cout << "exception: " << e.what() << '\n';
    }
}

// > g++ scratchpad.cpp; ./a.out
// exception: GSL: Precondition failure at ...

#endif

#if SNIPPET32

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

int
test(int i)
{
    Expects(i >= 0 && i < 41);
    i++;

    Ensures(i < 42);
    return i;
}

int main(void)
{
    test(0);

    try {
        test(42);
    }
    catch(const gsl::fail_fast &e) {
        std::cout << "exception: " << e.what() << '\n';
    }
}

// > g++ scratchpad.cpp; ./a.out
// exception: GSL: Precondition failure at ...

#endif

#if SNIPPET33

#include <gsl/gsl>
#include <iostream>

int
test(int i)
{
    Expects(i < 42);
    i = 42;
    Ensures(i == 42);

    return i;
}

int main(void)
{
    std::cout << test(0) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET34

#define concat1(a,b) a ## b
#define concat2(a,b) concat1(a,b)
#define ___ concat2(dont_care, __COUNTER__)

#include <gsl/gsl>
#include <iostream>

int main(void)
{
    auto ___ = gsl::finally([]{
        std::cout << "Hello World\n";
    });
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET35

#include <gsl/gsl>
#include <iostream>

int main(void)
{
    uint64_t val = 42;

    auto val1 = gsl::narrow<uint32_t>(val);
    auto val2 = gsl::narrow_cast<uint32_t>(val);
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET36

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

int main(void)
{
    uint64_t val = 0xFFFFFFFFFFFFFFFF;

    try {
        gsl::narrow<uint32_t>(val);
    }
    catch(...) {
        std::cout << "narrow failed\n";
    }
}

// > g++ scratchpad.cpp; ./a.out
// narrow failed

#endif
