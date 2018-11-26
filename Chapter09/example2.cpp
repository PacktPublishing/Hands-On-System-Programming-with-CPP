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
#include <vector>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

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
    using is_always_equal = std::true_type;

public:

    myallocator()
    {
        std::cout << this << " constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept
    { (void) other; }

    pointer allocate(size_type n)
    {
        if (auto ptr = static_cast<pointer>(malloc(sizeof(T) * n))) {
            std::cout << this << "  A [" << n << "]: " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void) n;

        std::cout << this << "  D [" << n << "]: " << p << '\n';
        free(p);
    }
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

TEST_CASE("constructor / destructor")
{
    std::list<int, myallocator<int>> mylist;
    mylist.emplace_back(42);
}

// 0x7ffe97b0e8e0 constructor, sizeof(T): 24
// 0x7ffe97b0e8e0  A [1]: 0x55c0793e8580
// 0x7ffe97b0e8e0  D [1]: 0x55c0793e8580

TEST_CASE("std::vector")
{
    std::vector<int, myallocator<int>> myvector;
    myvector.emplace_back(42);
    myvector.emplace_back(42);
    myvector.emplace_back(42);
}

// 0x7ffe1db8e2d0 constructor, sizeof(T): 4
// 0x7ffe1db8e2d0  A [1]: 0x55bf9dbdd550
// 0x7ffe1db8e2d0  A [2]: 0x55bf9dbebe90
// 0x7ffe1db8e2d0  D [1]: 0x55bf9dbdd550
// 0x7ffe1db8e2d0  A [4]: 0x55bf9dbdd550
// 0x7ffe1db8e2d0  D [2]: 0x55bf9dbebe90
// 0x7ffe1db8e2d0  D [4]: 0x55bf9dbdd550

TEST_CASE("std::deque")
{
    std::deque<int, myallocator<int>> mydeque;
    mydeque.emplace_back(42);
    mydeque.emplace_back(42);
    mydeque.emplace_back(42);
}

// 0x7ffdea986f30 constructor, sizeof(T): 4
// 0x7ffdea986e67  A [8]: 0x55d6822b0da0
// 0x7ffdea986f30  A [128]: 0x55d6822afaf0
// 0x7ffdea986f30  D [128]: 0x55d6822afaf0
// 0x7ffdea986e67  D [8]: 0x55d6822b0da0

TEST_CASE("std::deque many")
{
    std::deque<int, myallocator<int>> mydeque;

    for (auto i = 0; i< 127; i++)
        mydeque.emplace_back(42);

    for (auto i = 0; i< 127; i++)
        mydeque.emplace_back(42);

    for (auto i = 0; i< 127; i++)
        mydeque.emplace_back(42);
}

// 0x7ffc5926b280 constructor, sizeof(T): 4
// 0x7ffc5926b1b7  A [8]: 0x560285cc0da0
// 0x7ffc5926b280  A [128]: 0x560285cbfaf0
// 0x7ffc5926b280  A [128]: 0x560285cc1660
// 0x7ffc5926b280  A [128]: 0x560285cc1bc0
// 0x7ffc5926b280  D [128]: 0x560285cbfaf0
// 0x7ffc5926b280  D [128]: 0x560285cc1660
// 0x7ffc5926b280  D [128]: 0x560285cc1bc0
// 0x7ffc5926b1b7  D [8]: 0x560285cc0da0
