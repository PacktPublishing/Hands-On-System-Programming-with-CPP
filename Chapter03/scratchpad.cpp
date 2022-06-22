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
    char c = 0x42;
    std::cout << c << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// B

#endif

#if SNIPPET02

#include <iostream>

int main(void)
{
    int i = 0x42;
    char c = 0x42;

    std::cout << i << '\n';
    std::cout << c << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 66
// B

#endif

#if SNIPPET03

#include <iostream>

int main(void)
{
    const char *str = "Hello World\n";
    std::cout << str;
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET04

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes_signed = sizeof(signed char);
    auto min_signed = std::numeric_limits<signed char>().min();
    auto max_signed = std::numeric_limits<signed char>().max();

    auto num_bytes_unsigned = sizeof(unsigned char);
    auto min_unsigned = std::numeric_limits<unsigned char>().min();
    auto max_unsigned = std::numeric_limits<unsigned char>().max();

    std::cout << "num bytes (signed): " << num_bytes_signed << '\n';
    std::cout << "min value (signed): " << +min_signed << '\n';
    std::cout << "max value (signed): " << +max_signed << '\n';

    std::cout << '\n';

    std::cout << "num bytes (unsigned): " << num_bytes_unsigned << '\n';
    std::cout << "min value (unsigned): " << +min_unsigned << '\n';
    std::cout << "max value (unsigned): " << +max_unsigned << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes (signed): 1
// min value (signed): -128
// max value (signed): 127

// num bytes (unsigned): 1
// min value (unsigned): 0
// max value (unsigned): 255

#endif

#if SNIPPET05

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes = sizeof(wchar_t);
    auto min = std::numeric_limits<wchar_t>().min();
    auto max = std::numeric_limits<wchar_t>().max();

    std::cout << "num bytes: " << num_bytes << '\n';
    std::cout << "min value: " << +min << '\n';
    std::cout << "max value: " << +max << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes: 4
// min value: -2147483648
// max value: 2147483647

#endif

#if SNIPPET06

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes_signed = sizeof(signed short int);
    auto min_signed = std::numeric_limits<signed short int>().min();
    auto max_signed = std::numeric_limits<signed short int>().max();

    auto num_bytes_unsigned = sizeof(unsigned short int);
    auto min_unsigned = std::numeric_limits<unsigned short int>().min();
    auto max_unsigned = std::numeric_limits<unsigned short int>().max();

    std::cout << "num bytes (signed): " << num_bytes_signed << '\n';
    std::cout << "min value (signed): " << min_signed << '\n';
    std::cout << "max value (signed): " << max_signed << '\n';

    std::cout << '\n';

    std::cout << "num bytes (unsigned): " << num_bytes_unsigned << '\n';
    std::cout << "min value (unsigned): " << min_unsigned << '\n';
    std::cout << "max value (unsigned): " << max_unsigned << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes (signed): 2
// min value (signed): -32768
// max value (signed): 32767

// num bytes (unsigned): 2
// min value (unsigned): 0
// max value (unsigned): 65535

#endif

#if SNIPPET07

#include <iostream>

int main(void)
{
    short int s = 42;

    std::cout << s << '\n';
    s++;
    std::cout << s << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// 42
// 43

#endif

#if SNIPPET08

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes_signed = sizeof(signed int);
    auto min_signed = std::numeric_limits<signed int>().min();
    auto max_signed = std::numeric_limits<signed int>().max();

    auto num_bytes_unsigned = sizeof(unsigned int);
    auto min_unsigned = std::numeric_limits<unsigned int>().min();
    auto max_unsigned = std::numeric_limits<unsigned int>().max();

    std::cout << "num bytes (signed): " << num_bytes_signed << '\n';
    std::cout << "min value (signed): " << min_signed << '\n';
    std::cout << "max value (signed): " << max_signed << '\n';

    std::cout << '\n';

    std::cout << "num bytes (unsigned): " << num_bytes_unsigned << '\n';
    std::cout << "min value (unsigned): " << min_unsigned << '\n';
    std::cout << "max value (unsigned): " << max_unsigned << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes (signed): 4
// min value (signed): -2147483648
// max value (signed): 2147483647

// num bytes (unsigned): 4
// min value (unsigned): 0
// max value (unsigned): 4294967295

#endif

#if SNIPPET09

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes_signed = sizeof(signed long int);
    auto min_signed = std::numeric_limits<signed long int>().min();
    auto max_signed = std::numeric_limits<signed long int>().max();

    auto num_bytes_unsigned = sizeof(unsigned long int);
    auto min_unsigned = std::numeric_limits<unsigned long int>().min();
    auto max_unsigned = std::numeric_limits<unsigned long int>().max();

    std::cout << "num bytes (signed): " << num_bytes_signed << '\n';
    std::cout << "min value (signed): " << min_signed << '\n';
    std::cout << "max value (signed): " << max_signed << '\n';

    std::cout << '\n';

    std::cout << "num bytes (unsigned): " << num_bytes_unsigned << '\n';
    std::cout << "min value (unsigned): " << min_unsigned << '\n';
    std::cout << "max value (unsigned): " << max_unsigned << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes (signed): 8
// min value (signed): -9223372036854775808
// max value (signed): 9223372036854775807

// num bytes (unsigned): 8
// min value (unsigned): 0
// max value (unsigned): 18446744073709551615

#endif

#if SNIPPET10

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes = sizeof(float);
    auto min = std::numeric_limits<float>().min();
    auto max = std::numeric_limits<float>().max();

    std::cout << "num bytes: " << num_bytes << '\n';
    std::cout << "min value: " << min << '\n';
    std::cout << "max value: " << max << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes: 4
// min value: 1.17549e-38
// max value: 3.40282e+38

#endif

#if SNIPPET11

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes = sizeof(double);
    auto min = std::numeric_limits<double>().min();
    auto max = std::numeric_limits<double>().max();

    std::cout << "num bytes: " << num_bytes << '\n';
    std::cout << "min value: " << min << '\n';
    std::cout << "max value: " << max << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes: 8
// min value: 2.22507e-308
// max value: 1.79769e+308

#endif

#if SNIPPET12

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes = sizeof(long double);
    auto min = std::numeric_limits<long double>().min();
    auto max = std::numeric_limits<long double>().max();

    std::cout << "num bytes: " << num_bytes << '\n';
    std::cout << "min value: " << min << '\n';
    std::cout << "max value: " << max << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes: 16
// min value: 3.3621e-4932
// max value: 1.18973e+4932

#endif

#if SNIPPET13

#include <iostream>
#include <limits>

int main(void)
{
    auto num_bytes = sizeof(bool);
    auto min = std::numeric_limits<bool>().min();
    auto max = std::numeric_limits<bool>().max();

    std::cout << "num bytes: " << num_bytes << '\n';
    std::cout << "min value: " << min << '\n';
    std::cout << "max value: " << max << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// num bytes: 1
// min value: 0
// max value: 1

#endif

#if SNIPPET14

#include <typeinfo>
#include <iostream>

#include <string>
#include <cstdlib>
#include <cxxabi.h>

#include <stdint.h>

template<typename T>
std::string type_name()
{
    int status;
    std::string name = typeid(T).name();

    auto demangled_name =
        abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

    if (status == 0) {
        name = demangled_name;
        std::free(demangled_name);
    }

    return name;
}

template<typename T1, typename T2>
void
are_equal()
{
    #define red "\033[1;31m"
    #define reset "\033[0m"

    std::cout << type_name<T1>() << " vs "
              << type_name<T2>() << '\n';

    if (sizeof(T1) == sizeof(T2)) {
        std::cout << "  - size: both == " << sizeof(T1) << '\n';
    }
    else {
        std::cout << red "  - size: "
                  << sizeof(T1)
                  << " != "
                  << sizeof(T2)
                  << reset "\n";
    }

    if (type_name<T1>() == type_name<T2>()) {
        std::cout << "  - name: both == " << type_name<T1>() << '\n';
    }
    else {
        std::cout << red "  - name: "
                  << type_name<T1>()
                  << " != "
                  << type_name<T2>()
                  << reset "\n";
    }
}

int main()
{
    are_equal<uint8_t, int8_t>();
    are_equal<uint8_t, uint32_t>();

    are_equal<signed char, int8_t>();
    are_equal<unsigned char, uint8_t>();

    are_equal<signed short int, int16_t>();
    are_equal<unsigned short int, uint16_t>();
    are_equal<signed int, int32_t>();
    are_equal<unsigned int, uint32_t>();
    are_equal<signed long int, int64_t>();
    are_equal<unsigned long int, uint64_t>();
    are_equal<signed long long int, int64_t>();
    are_equal<unsigned long long int, uint64_t>();
}

// > g++ scratchpad.cpp; ./a.out
// unsigned char vs signed char
//   - size: both == 1
//   - name: unsigned char != signed char
// unsigned char vs unsigned int
//   - size: 1 != 4
//   - name: unsigned char != unsigned int
// signed char vs signed char
//   - size: both == 1
//   - name: both == signed char
// unsigned char vs unsigned char
//   - size: both == 1
//   - name: both == unsigned char
// short vs short
//   - size: both == 2
//   - name: both == short
// unsigned short vs unsigned short
//   - size: both == 2
//   - name: both == unsigned short
// int vs int
//   - size: both == 4
//   - name: both == int
// unsigned int vs unsigned int
//   - size: both == 4
//   - name: both == unsigned int
// long vs long
//   - size: both == 8
//   - name: both == long
// unsigned long vs unsigned long
//   - size: both == 8
//   - name: both == unsigned long
// long long vs long
//   - size: both == 8
//   - name: long long != long
// unsigned long long vs unsigned long
//   - size: both == 8
//   - name: unsigned long long != unsigned long

#endif

#if SNIPPET15

#include <iostream>

struct mystruct {
    uint64_t data1;
    uint64_t data2;
};

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif

#if SNIPPET16

#include <iostream>

struct mystruct {
    uint64_t data1;
    uint16_t data2;
};

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif

#if SNIPPET17

#include <iostream>

struct mystruct {
    uint16_t data1;
    uint64_t data2;
};

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif

#if SNIPPET18

#include <iostream>

int main()
{
    int16_t s = 42;
    auto result = s + 42;
    std::cout << "size: " << sizeof(result) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 4

#endif

#if SNIPPET19

#include <iostream>

struct mystruct {
    uint16_t data1;
    uint16_t data2;
};

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 4

#endif

#if SNIPPET20

#include <iostream>

struct mystruct {
    uint16_t data1 : 2, data2 : 14;
    uint64_t data3;
};

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif

#if SNIPPET21

#include <iostream>

#pragma pack(push, 1)
struct mystruct {
    uint64_t data1;
    uint16_t data2;
};
#pragma pack(pop)

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 10

#endif

#if SNIPPET22

#include <iostream>

#pragma pack(push, 1)
struct mystruct {
    uint16_t data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 10

#endif

#if SNIPPET23

#include <iostream>

#pragma pack(push, 1)
struct mystruct {
    uint16_t data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    mystruct s;
    std::cout << "addr: " << &s << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 0x7fffd11069cf

#endif

#if SNIPPET24

#include <iostream>

#pragma pack(push, 1)
struct alignas(16) mystruct {
    uint16_t data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    mystruct s;
    std::cout << "addr: " << &s << '\n';
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// addr: 0x7fff44ee3f40
// size: 16

#endif

#if SNIPPET25

#include <iostream>

#pragma pack(push, 1)
struct alignas(16) mystruct {
    uint16_t data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    mystruct s;
    std::cout << "addr data1: " << &s.data1 << '\n';
    std::cout << "addr data2: " << &s.data2 << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// addr data1: 0x7ffc45dd8c90
// addr data2: 0x7ffc45dd8c92

#endif

#if SNIPPET26

#include <iostream>

#pragma pack(push, 1)
struct mystruct {
    uint16_t *data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif

#if SNIPPET27

#include <iostream>

#pragma pack(push, 1)
struct mystruct {
    uintptr_t data1;
    uint64_t data2;
};
#pragma pack(pop)

int main()
{
    std::cout << "size: " << sizeof(mystruct) << '\n';
}

// > g++ scratchpad.cpp; ./a.out
// size: 16

#endif
