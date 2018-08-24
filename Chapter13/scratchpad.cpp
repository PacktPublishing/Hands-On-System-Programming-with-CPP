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
// Section: POSIX Style Error Handling
// -----------------------------------------------------------------------------

#if SNIPPET01

#include <string.h>
#include <iostream>

int myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        return -1;
    }

    return 0;
}

main()
{
    if (myfunc(1) == 0) {
        std::cout << "success\n";
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (myfunc(42) == 0) {
        std::cout << "success\n";
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: Invalid argument

#endif

#if SNIPPET02

#include <string.h>
#include <iostream>

int myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        return 0;
    }

    return 42;
}

main()
{
    if (auto handle = myfunc(1); handle != 0) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (auto handle = myfunc(42); handle != 0) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success: 42
// failure: Invalid argument

#endif

#if SNIPPET03

#include <string.h>
#include <iostream>

std::pair<int, bool>
myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        return {0, false};
    }

    return {42, true};
}

main()
{
    if (auto [handle, success] = myfunc(1); success) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (auto [handle, success] = myfunc(42); success) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success: 42
// failure: Invalid argument

#endif

#if SNIPPET03a

#include <string.h>
#include <iostream>

int myfunc(int val, int &error)
{
    if (val == 42) {
        error = EINVAL;
        return 0;
    }

    return 42;
}

main()
{
    int error = 0;

    if (auto handle = myfunc(1, error); error == 0) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(error) << '\n';
    }

    if (auto handle = myfunc(42, error); error == 0) {
        std::cout << "success: " << handle << '\n';
    }
    else {
        std::cout << "failure: " << strerror(error) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success: 42
// failure: Invalid argument

#endif

#if SNIPPET04

#include <string.h>
#include <iostream>

int myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        return -1;
    }

    return 0;
}

int nested1(int val)
{
    if (auto ret = myfunc(val); ret != 0) {
        std::cout << "nested1 failure: " << strerror(errno) << '\n';
        return ret;
    }
    else {
        std::cout << "nested1 success\n";
    }

    return 0;
}

int nested2(int val)
{
    if (auto ret = nested1(val); ret != 0) {
        std::cout << "nested2 failure: " << strerror(errno) << '\n';
        return ret;
    }
    else {
        std::cout << "nested2 success\n";
    }

    return 0;
}

main()
{
    if (nested2(1) == 0) {
        std::cout << "main success\n";
    }
    else {
        std::cout << "main failure: " << strerror(errno) << '\n';
    }

    if (nested2(42) == 0) {
        std::cout << "main success\n";
    }
    else {
        std::cout << "main failure: " << strerror(errno) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// nested1 success
// nested2 success
// main success
// nested1 failure: Invalid argument
// nested2 failure: Invalid argument
// main failure: Invalid argument

#endif

#if SNIPPET05

#include <string.h>
#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

int myfunc(int val)
{
    myclass c{};

    if (val == 42) {
        errno = EINVAL;
        return -1;
    }

    return 0;
}

main()
{
    if (myfunc(1) == 0) {
        std::cout << "success\n";
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (myfunc(42) == 0) {
        std::cout << "success\n";
    }
    else {
        std::cout << "failure: " << strerror(errno) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// destructor called
// success
// destructor called
// failure: Invalid argument

#endif

// -----------------------------------------------------------------------------
// Section: Set Jump Exceptions
// -----------------------------------------------------------------------------

#if SNIPPET06

#include <string.h>
#include <csetjmp>

#include <iostream>

jmp_buf jb;

void myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        std::longjmp(jb, -1);
    }
}

main()
{
    if (setjmp(jb) == -1) {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    myfunc(1);
    std::cout << "success\n";

    myfunc(42);
    std::cout << "success\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: Invalid argument

#endif

#if SNIPPET07

#include <string.h>
#include <csetjmp>

#include <iostream>

jmp_buf jb;

int myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        std::longjmp(jb, -1);
    }

    return 42;
}

main()
{
    if (setjmp(jb) == -1) {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    auto handle1 = myfunc(1);
    std::cout << "success: " << handle1 << '\n';

    auto handle2 = myfunc(42);
    std::cout << "success: " << handle2 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success: 42
// failure: Invalid argument

#endif

#if SNIPPET08

#include <string.h>
#include <csetjmp>

#include <iostream>

jmp_buf jb;

void myfunc(int val)
{
    if (val == 42) {
        errno = EINVAL;
        std::longjmp(jb, -1);
    }
}

int nested1(int val)
{
    myfunc(val);
    std::cout << "nested1 success\n";
}

int nested2(int val)
{
    nested1(val);
    std::cout << "nested2 success\n";
}

main()
{
    if (setjmp(jb) == -1) {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    nested2(1);
    std::cout << "main success\n";

    nested2(42);
    std::cout << "main success\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// nested1 success
// nested2 success
// main success
// failure: Invalid argument

#endif

#if SNIPPET09

#include <string.h>
#include <csetjmp>

#include <iostream>

void myfunc(int val, jmp_buf &jb)
{
    if (val == 42) {
        std::longjmp(jb, EINVAL);
    }
}

main()
{
    jmp_buf jb;

    if (auto ret = setjmp(jb); ret > 0) {
        std::cout << "failure: " << strerror(ret) << '\n';
        exit(EXIT_FAILURE);
    }

    myfunc(1, jb);
    std::cout << "success\n";

    myfunc(42, jb);
    std::cout << "success\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: Invalid argument

#endif

#if SNIPPET10

#include <string.h>
#include <csetjmp>

#include <iostream>

jmp_buf jb;

class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

void myfunc(int val)
{
    myclass c{};

    if (val == 42) {
        errno = EINVAL;
        std::longjmp(jb, -1);
    }
}

main()
{
    if (setjmp(jb) == -1) {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    myfunc(1);
    std::cout << "success\n";

    myfunc(42);
    std::cout << "success\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// destructor called
// success
// failure: Invalid argument

#endif

// -----------------------------------------------------------------------------
// Section: Exception Support in C++
// -----------------------------------------------------------------------------

#if SNIPPET11

#include <string.h>
#include <iostream>

void myfunc(int val)
{
    if (val == 42) {
        throw EINVAL;
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(int ret) {
        std::cout << "failure: " << strerror(ret) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: Invalid argument

#endif

#if SNIPPET12

#include <string.h>
#include <iostream>

int myfunc(int val)
{
    if (val == 42) {
        throw EINVAL;
    }

    return 42;
}

main()
{
    try {
        auto handle1 = myfunc(1);
        std::cout << "success: " << handle1 << '\n';

        auto handle2 = myfunc(42);
        std::cout << "success: " << handle2 << '\n';
    }
    catch(int ret) {
        std::cout << "failure: " << strerror(ret) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success: 42
// failure: Invalid argument

#endif

#if SNIPPET13

#include <string.h>
#include <iostream>

void myfunc(int val)
{
    if (val == 42) {
        throw EINVAL;
    }
}

int nested1(int val)
{
    myfunc(val);
    std::cout << "nested1 success\n";
}

int nested2(int val)
{
    nested1(val);
    std::cout << "nested2 success\n";
}

main()
{
    try {
        nested2(1);
        std::cout << "main success\n";

        nested2(42);
        std::cout << "main success\n";
    }
    catch(int ret) {
        std::cout << "failure: " << strerror(ret) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// nested1 success
// nested2 success
// main success
// failure: Invalid argument

#endif

#if SNIPPET14

#include <string.h>
#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

void myfunc(int val)
{
    myclass c{};

    if (val == 42) {
        throw EINVAL;
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(int ret) {
        std::cout << "failure: " << strerror(ret) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// destructor called
// success
// destructor called
// failure: Invalid argument

#endif

#if SNIPPET15

#include <string.h>
#include <iostream>

void myfunc(int val)
{
    if (val == 42) {
        throw std::runtime_error("invalid val");
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(std::exception &e) {
        std::cout << "failure: " << e.what() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: invalid val

#endif

#if SNIPPET16

#include <string.h>
#include <iostream>

void myfunc(int val)
{
    if (val == 42) {
        throw -1;
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(...) {
        std::cout << "failure\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure

#endif

#if SNIPPET17

#include <string.h>
#include <iostream>

class myexception : public std::exception
{
    int m_error{0};

public:

    myexception(int error) noexcept :
        m_error{error}
    { }

	const char *
    what() const noexcept
    {
    	return "error";
    }

    int error()
    {
        return m_error;
    }
};

void myfunc(int val)
{
    if (val == 42) {
        throw myexception(42);
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(myexception &e) {
        std::cout << "failure: " << std::to_string(e.error()) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: 42

#endif

#if SNIPPET18

#include <string.h>
#include <iostream>

class myexception : public std::runtime_error
{
public:
    myexception(int error) noexcept :
        std::runtime_error("error: " + std::to_string(42))
    { }
};

void myfunc(int val)
{
    if (val == 42) {
        throw myexception(42);
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(std::exception &e) {
        std::cout << "failure: " << e.what() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// success
// failure: error: 42

#endif

#if SNIPPET19

#include <string.h>
#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "uncaught_exceptions: "
                  << std::uncaught_exceptions() << '\n';
    }
};

void myfunc(int val)
{
    myclass c{};

    if (val == 42) {
        throw EINVAL;
    }
}

main()
{
    try {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(int ret) {
        std::cout << "failure: " << strerror(ret) << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// uncaught_exceptions: 0
// success
// uncaught_exceptions: 1
// failure: Invalid argument

#endif
