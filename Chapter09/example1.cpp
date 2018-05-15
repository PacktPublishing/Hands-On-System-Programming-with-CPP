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
#include <deque>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

// -----------------------------------------------------------------------------
// Allocator Definition
// -----------------------------------------------------------------------------

template<typename T>
class myallocator
{
public:

    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;

public:

    myallocator() = default;

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept
    { (void) other; }

    pointer allocate(size_type n)
    {
        if (auto ptr = static_cast<pointer>(malloc(sizeof(T) * n))) {
            std::cout << " - size: " << n << "   ptr: " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    { (void) n; free(p); }
};

template <typename T1, typename T2>
bool operator==(const myallocator<T1> &, const myallocator<T2> &)
{ return true; }

template <typename T1, typename T2>
bool operator!=(const myallocator<T1> &, const myallocator<T2> &)
{ return false; }

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

struct myclass
{
    int data1;
    int data2;
};

TEST_CASE("allocate single object")
{
    std::cout << "allocate single object\n";

    myallocator<myclass> myalloc;

    auto ptr = myalloc.allocate(1);
    myalloc.deallocate(ptr, 1);
}

TEST_CASE("allocate multiple objects")
{
    std::cout << "allocate multiple objects\n";

    myallocator<myclass> myalloc;

    auto ptr = myalloc.allocate(5);
    myalloc.deallocate(ptr, 5);
}

TEST_CASE("std::list single allocations")
{
    std::cout << "std::list single allocations\n";

    std::list<myclass, myallocator<myclass>> mylist;
    mylist.emplace_back();
    mylist.emplace_back();
    mylist.emplace_back();
}

TEST_CASE("std::deque multiple allocations")
{
    std::cout << "std::deque multiple allocations\n";

    std::deque<myclass, myallocator<myclass>> mydeque;
    mydeque.emplace_back();
    mydeque.emplace_back();
    mydeque.emplace_back();
}

TEST_CASE("demo statelessness")
{
    std::cout << "demo statelessness\n";

    myallocator<myclass> myalloc1;
    myallocator<myclass> myalloc2;

    auto ptr = myalloc1.allocate(5);
    myalloc2.deallocate(ptr, 5);
}
