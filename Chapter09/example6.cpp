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
#include <vector>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// -----------------------------------------------------------------------------
// Allocator Definition
// -----------------------------------------------------------------------------

template<typename T, std::size_t Alignment = 0x40>
class myallocator
{
public:

    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::true_type;

    template<typename U> struct rebind {
        using other = myallocator<U, Alignment>;
    };

public:

    myallocator()
    { }

    template <typename U>
    myallocator(const myallocator<U, Alignment> &other) noexcept
    { (void) other; }

    pointer allocate(size_type n)
    {
        if (auto ptr = aligned_alloc(Alignment, sizeof(T) * n)) {
            return static_cast<pointer>(ptr);
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void) n;
        free(p);
    }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TEST_CASE("allocate single object")
{
    myallocator<int> myalloc;

    auto ptr = myalloc.allocate(1);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 1);
}

// 0x561d512b6500

TEST_CASE("allocate multiple objects")
{
    myallocator<int> myalloc;

    auto ptr = myalloc.allocate(42);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 42);
}

// 0x55dcdcb41500

TEST_CASE("std::vector single element")
{
    std::vector<int, myallocator<int>> myvector;
    myvector.emplace_back(42);

    std::cout << myvector.data() << '\n';
}

// 0x55f875a0f500
