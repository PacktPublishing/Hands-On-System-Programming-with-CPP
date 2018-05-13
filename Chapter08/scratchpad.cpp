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

// HEADING 1: Opening a File
// HEADING 2: Reading and Writing to a File
// HEADING 3: File Utilities
// HEADING 4: Logger Example
// HEADING 5: Tail File Example
// HEADING 6: C++ vs mmap Benchmark Example
// SKILL 1: Learn to open a file using C++, including the various permission modifiers
// SKILL 2: Learn how to read and write to a file using C++’s APIs
// SKILL 3: Learn what utility facilities C++’s APIs provide including getting a file’s size, random file access, synchronization and error handling.
// SKILL 4: Learn how to create a simple logger for debugging.
// SKILL 5: Learn how to tail a file using C++ and the POSIX APIs. This example can be used to read the output of the logger example
// SKILL 6: Learn how to benchmark the performance difference between C++’s file APIs vs. raw POSIX memory mapping.

// -----------------------------------------------------------------------------
// Section: Opening a File
// -----------------------------------------------------------------------------

#if 1

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("testff.txt")) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt"); file.is_open()) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    auto file = std::fstream();
    if (file.open("test.txt"); file.is_open()) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        std::cout << file.is_open() << '\n';
        file.close();
        std::cout << file.is_open() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// true
// false

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::in | std::ios::binary;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::in;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::out | std::ios::binary;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::out;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::out | std::ios::binary | std::ios::ate;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::out | std::ios::binary | std::ios::ate;
    if (auto file = std::fstream("test.txt", mode); file.seekp(0)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::out | std::ios::binary | std::ios::app;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    constexpr auto mode = std::ios::in | std::ios::out | std::ios::trunc;
    if (auto file = std::fstream("test.txt", mode)) {
        std::cout << "success\n";
    }
}

// > g++ -std=c++17 scratchpad.cpp; touch test.txt; ./a.out
// success

#endif

// -----------------------------------------------------------------------------
// Section: Reading and Writing to a File
// -----------------------------------------------------------------------------

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::string hello, world;
        file >> hello >> world;
        std::cout << hello << " " << world << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        int answer;
        file >> answer;
        std::cout << "The answer is: " << answer << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "42" > test.txt; ./a.out
// The answer is: 42

#endif

#if 0

// > g++ -std=c++17 scratchpad.cpp; echo "not_a_number" > test.txt; ./a.out
// The answer is: 42

#endif

#if 0

#include <fstream>
#include <iostream>

struct myclass
{
    std::string hello;
    std::string world;
};

std::fstream &operator >>(std::fstream &is, myclass &obj)
{
    is >> obj.hello;
    is >> obj.world;

    return is;
}

std::ostream &operator<<(std::ostream &os, const myclass &obj)
{
    os << obj.hello;
    os << ' ';
    os << obj.world;

    return os;
}

int main()
{
    if (auto file = std::fstream("test.txt")) {
        myclass obj;
        file >> obj;
        std::cout << obj << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        char c = file.get();
        std::cout << c << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// H

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        char buf[25] = {};
        file.read(buf, 11);
        std::cout << buf << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

template<typename T, std::size_t N>
void myread(std::fstream &file, T (&str)[N], std::size_t count)
{
    if (count >= N) {
        throw std::out_of_range("file.read out of bounds");
    }

    file.read(static_cast<char *>(str), count);
}

int main()
{
    if (auto file = std::fstream("test.txt")) {
        char buf[25] = {};
        myread(file, buf, 11);
        std::cout << buf << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.gcount() << '\n';
        char c = file.get();
        std::cout << file.gcount() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// 0
// 1

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellg() << '\n';
        char c = file.get();
        std::cout << file.tellg() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// 0
// 1

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellg() << '\n';
        char c = file.peek();
        std::cout << file.tellg() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// 0
// 0

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellg() << '\n';
        file.ignore(1);
        std::cout << file.tellg() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// 0
// 1

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellg() << '\n';
        file.seekg(1);
        std::cout << file.tellg() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// 0
// 1

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        char buf[25] = {};
        file.getline(buf, 25, '\n');
        std::cout << buf << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::string str;
        std::getline(file, str);
        std::cout << str << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file.sync();
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "Hello World" > test.txt; ./a.out

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file << "The answer is: " << 42 << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// The answer is: 42

#endif

#if 0

#include <fstream>
#include <iostream>

struct myclass
{
    std::string hello{"Hello"};
    std::string world{"World"};
};

std::fstream &operator <<(std::fstream &os, const myclass &obj)
{
    os << obj.hello;
    os << ' ';
    os << obj.world;

    return os;
}

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file << myclass{} << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file.put('H');
        file.put('\n');
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// H

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file.write("Hello World\n", 12);
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file.write("Hello World\n", 100);
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello World
// ;�����D���d)��������$=���DR����d���d�����[

#endif

#if 0

#include <string.h>

#include <fstream>
#include <iostream>

void
mywrite(std::fstream &file, const char *str, std::size_t count)
{
    if (count > strlen(str)) {
        throw std::out_of_range("file.write out of bounds");
    }

    file.write(str, count);
}

int main()
{
    if (auto file = std::fstream("test.txt")) {
        mywrite(file, "Hello World\n", 100);
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// terminate called after throwing an instance of 'std::out_of_range'
//   what():  file.write out of bounds
// Aborted (core dumped)

#endif

#if 0

#include <string.h>

#include <fstream>
#include <iostream>

void
mywrite(std::fstream &file, const char *str, std::size_t count)
{
    if (count > strlen(str)) {
    std::cerr << count << "  " << strlen(str) << '\n';
        throw std::out_of_range("file.write out of bounds");
    }

    file.write(str, count);
}

int main()
{
    if (auto file = std::fstream("test.txt")) {
        const char str1[6] = {'H','e','l','l','o','\n'};
        const char str2[6] = {'W','o','r','l','d','\n'};
        mywrite(file, str1, 12);
        mywrite(file, str2, 6);
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello
// World
// World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellp() << '\n';
        file << "Hello";
        std::cout << file.tellp() << '\n';
        file << ' ';
        std::cout << file.tellp() << '\n';
        file << "World";
        std::cout << file.tellp() << '\n';
        file << '\n';
        std::cout << file.tellp() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// 0
// 5
// 6
// 11
// 12
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        std::cout << file.tellp() << '\n';
        file << "Hello World\n";
        std::cout << file.tellp() << '\n';
        file.seekp(0);
        std::cout << file.tellp() << '\n';
        file << "The answer is: " << 42 << '\n';
        std::cout << file.tellp() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// 0
// 12
// 0
// 18
// The answer is: 42

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    if (auto file = std::fstream("test.txt")) {
        file.flush();
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        std::cout << "good: " << file.good() << '\n';
        std::cout << "fail: " << file.fail() << '\n';
        std::cout << "bad: " << file.bad() << '\n';
        std::cout << "eof: " << file.eof() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// good: true
// fail: false
// bad: false
// eof: false
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        if (!file) {
            std::cout << "failed\n";
        }
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        if (file) {
            std::cout << "success\n";
        }
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// success
// Hello World

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        int answer;
        std::cout << file.good() << '\n';
        file >> answer;
        std::cout << file.good() << '\n';
        file.clear();
        std::cout << file.good() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "not_a_number" > test.txt; ./a.out
// true
// false
// true

#endif

#if 0

#include <fstream>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    if (auto file = std::fstream("test.txt")) {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        file.clear();
    }
}

// > g++ -std=c++17 scratchpad.cpp; echo "" > test.txt; ./a.out; cat test.txt
// success
// Hello World

#endif

// -----------------------------------------------------------------------------
// Section: File Utilities
// -----------------------------------------------------------------------------

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::filesystem::is_block_file("/dev/sda1") << '\n';
    std::cout << std::filesystem::is_character_file("/dev/random") << '\n';
    std::cout << std::filesystem::is_directory("/dev") << '\n';
    std::cout << std::filesystem::is_empty("/dev") << '\n';
    std::cout << std::filesystem::is_fifo("scratchpad.cpp") << '\n';
    std::cout << std::filesystem::is_other("scratchpad.cpp") << '\n';
    std::cout << std::filesystem::is_regular_file("scratchpad.cpp") << '\n';
    std::cout << std::filesystem::is_socket("scratchpad.cpp") << '\n';
    std::cout << std::filesystem::is_symlink("scratchpad.cpp") << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// true
// true
// false
// false
// false
// true
// false
// false

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::filesystem::exists("/dev") << '\n';
    std::cout << std::filesystem::exists("/dev/random") << '\n';
    std::cout << std::filesystem::exists("scratchpad.cpp") << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// true
// true

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::filesystem::current_path() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    std::cout << std::filesystem::relative(path) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "."

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::filesystem::canonical(".") << '\n';
    std::cout << std::filesystem::canonical("../chapter_8") << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::filesystem::absolute("../chapter_8") << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/../chapter_8"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path1 = std::filesystem::path{"."};
    auto path2 = std::filesystem::path{"../chapter_8"};
    auto path3 = std::filesystem::path{"../chapter_8/../chapter_8"};
    auto path4 = std::filesystem::current_path();
    auto path5 = std::filesystem::current_path() / "../chapter_8/";

    std::cout << std::boolalpha;
    std::cout << std::filesystem::equivalent(path1, path2) << '\n';
    std::cout << std::filesystem::equivalent(path1, path3) << '\n';
    std::cout << std::filesystem::equivalent(path1, path4) << '\n';
    std::cout << std::filesystem::equivalent(path1, path5) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// true
// true
// true

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path1 = std::filesystem::path{"."};
    auto path2 = std::filesystem::path{"../chapter_8"};
    auto path3 = std::filesystem::path{"../chapter_8/../chapter_8"};
    auto path4 = std::filesystem::current_path();
    auto path5 = std::filesystem::current_path() / "../chapter_8/";

    std::cout << std::boolalpha;
    std::cout << (path1 == path2) << '\n';
    std::cout << (path1 == path3) << '\n';
    std::cout << (path1 == path4) << '\n';
    std::cout << (path1 == path5) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// false
// false
// false
// false

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path += "/scratchpad.cpp";

    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << path << '\n';
    path.remove_filename();
    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << path << '\n';
    path.replace_filename("test.cpp");
    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/test.cpp"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << path << '\n';
    path.replace_extension("txt");
    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.txt"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << path << '\n';
    path.clear();
    std::cout << path << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"
// ""

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << std::boolalpha;
    std::cout << path.root_name() << '\n';
    std::cout << path.root_directory() << '\n';
    std::cout << path.root_path() << '\n';
    std::cout << path.relative_path() << '\n';
    std::cout << path.parent_path() << '\n';
    std::cout << path.filename() << '\n';
    std::cout << path.stem() << '\n';
    std::cout << path.extension() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// ""
// "/"
// "/"
// "home/user/Hands-On-System-Programming-with-CPP/chapter_8/scratchpad.cpp"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8"
// "scratchpad.cpp"
// "scratchpad"
// ".cpp"

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "scratchpad.cpp";

    std::cout << std::boolalpha;
    std::cout << path.empty() << '\n';
    std::cout << path.has_root_path() << '\n';
    std::cout << path.has_root_name() << '\n';
    std::cout << path.has_root_directory() << '\n';
    std::cout << path.has_relative_path() << '\n';
    std::cout << path.has_parent_path() << '\n';
    std::cout << path.has_filename() << '\n';
    std::cout << path.has_stem() << '\n';
    std::cout << path.has_extension() << '\n';
    std::cout << path.is_absolute() << '\n';
    std::cout << path.is_relative() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// false
// true
// false
// true
// true
// true
// true
// true
// true
// true
// false

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "test";

    std::cout << std::boolalpha;
    std::cout << std::filesystem::create_directory(path) << '\n';
    std::cout << std::filesystem::remove(path) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// true

#endif

#if 0

#include <iostream>
#include <filesystem>

int main()
{
    auto path1 = std::filesystem::current_path();
    auto path2 = std::filesystem::current_path();
    path1 /= "test1";
    path2 /= "test2";

    std::cout << std::boolalpha;
    std::cout << std::filesystem::create_directory(path1) << '\n';
    std::filesystem::rename(path1, path2);
    std::cout << std::filesystem::remove(path1) << '\n';
    std::cout << std::filesystem::remove(path2) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// false
// true

#endif

#if 0

#include <fstream>
#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "test";

    std::cout << std::boolalpha;
    std::cout << std::filesystem::create_directory(path) << '\n';

    std::fstream(path / "test1.txt", std::ios::app);
    std::fstream(path / "test2.txt", std::ios::app);
    std::fstream(path / "test3.txt", std::ios::app);

    std::cout << std::filesystem::remove_all(path) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// 4

#endif

#if 0

#include <fstream>
#include <iostream>
#include <filesystem>

int main()
{
    auto path = std::filesystem::current_path();
    path /= "test";

    std::cout << std::boolalpha;
    std::cout << std::filesystem::create_directory(path) << '\n';

    std::fstream(path / "test1.txt", std::ios::app);
    std::fstream(path / "test2.txt", std::ios::app);
    std::fstream(path / "test3.txt", std::ios::app);

    for(const auto &p: std::filesystem::directory_iterator(path)) {
        std::cout << p << '\n';
    }

    std::cout << std::filesystem::remove_all(path) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// true
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/test/test1.txt"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/test/test3.txt"
// "/home/user/Hands-On-System-Programming-with-CPP/chapter_8/test/test2.txt"
// 4

#endif

#if 0

#include <fstream>
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << std::filesystem::temp_directory_path() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lstdc++fs; ./a.out
// "/tmp"

#endif
