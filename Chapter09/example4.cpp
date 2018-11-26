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

class myallocator_object
{
public:

    using size_type = std::size_t;

public:

    void *allocate(size_type size)
    {
        if (auto ptr = malloc(size)) {
            std::cout << this << "  A " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(void *ptr)
    {
        std::cout << this << "  D " << ptr << '\n';
        free(ptr);
    }
};

template<typename T>
class myallocator
{
public:

    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::false_type;

public:

    myallocator() :
        m_object{std::make_shared<myallocator_object>()}
    {
        std::cout << this << " constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept :
        m_object{other.m_object}
    {
        std::cout << this << " copy constructor (U), sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator(myallocator &&other) noexcept :
        m_object{std::move(other.m_object)}
    {
        std::cout << this << " move constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(myallocator &&other) noexcept
    {
        std::cout << this << " move assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_object = std::move(other.m_object);
        return *this;
    }

    myallocator(const myallocator &other) noexcept :
        m_object{other.m_object}
    {
        std::cout << this << " copy constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(const myallocator &other) noexcept
    {
        std::cout << this << " copy assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_object = other.m_object;
        return *this;
    }

    pointer allocate(size_type n)
    {
        auto ptr = m_object->allocate(sizeof(T) * n);
        return static_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type n)
    {
        (void) n;
        return m_object->deallocate(p);
    }

private:

    std::shared_ptr<myallocator_object> m_object;

    template <typename T1, typename T2>
    friend bool operator==(const myallocator<T1> &lhs, const myallocator<T2> &rhs);

    template <typename T1, typename T2>
    friend bool operator!=(const myallocator<T1> &lhs, const myallocator<T2> &rhs);

    template <typename U>
    friend class myallocator;
};

template <typename T1, typename T2>
bool operator==(const myallocator<T1> &lhs, const myallocator<T2> &rhs)
{ return lhs.m_object.get() == rhs.m_object.get(); }

template <typename T1, typename T2>
bool operator!=(const myallocator<T1> &lhs, const myallocator<T2> &rhs)
{ return lhs.m_object.get() != rhs.m_object.get(); }

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TEST_CASE("constructor / destructor")
{
    std::list<int, myallocator<int>> mylist;
    mylist.emplace_back(42);
}

// 0x7ffd65a15ce0 constructor, sizeof(T): 24
// 0x55c4867c3a80  A [1]: 0x55c4867d23b0
// 0x55c4867c3a80  D [1]: 0x55c4867d23b0

TEST_CASE("copy")
{
    std::list<int, myallocator<int>> mylist1;
    std::list<int, myallocator<int>> mylist2;

    mylist1.emplace_back(42);
    mylist1.emplace_back(42);

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist2 = mylist1;
    std::cout << "----------------------------------------\n";

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);
}

// 0x7ffd65a15cb0 constructor, sizeof(T): 24
// 0x7ffd65a15ce0 constructor, sizeof(T): 24
// 0x55c4867c3a80  A [1]: 0x55c4867b9210
// 0x55c4867c3a80  A [1]: 0x55c4867baec0
// 0x55c4867d23c0  A [1]: 0x55c4867c89c0
// 0x55c4867d23c0  A [1]: 0x55c4867cb050
// ----------------------------------------
// ----------------------------------------
// 0x55c4867d23c0  A [1]: 0x55c4867c39f0
// 0x55c4867d23c0  A [1]: 0x55c4867c3a10
// 0x55c4867d23c0  D [1]: 0x55c4867c89c0
// 0x55c4867d23c0  D [1]: 0x55c4867cb050
// 0x55c4867d23c0  D [1]: 0x55c4867c39f0
// 0x55c4867d23c0  D [1]: 0x55c4867c3a10
// 0x55c4867c3a80  D [1]: 0x55c4867b9210
// 0x55c4867c3a80  D [1]: 0x55c4867baec0

TEST_CASE("move")
{
    std::list<int, myallocator<int>> mylist1;
    std::list<int, myallocator<int>> mylist2;

    mylist1.emplace_back(42);
    mylist1.emplace_back(42);

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist2 = std::move(mylist1);
    std::cout << "----------------------------------------\n";

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);
}

// 0x7ffd65a15cb0 constructor, sizeof(T): 24
// 0x7ffd65a15ce0 constructor, sizeof(T): 24
// 0x55c4867c3a80  A [1]: 0x55c4867c3a10
// 0x55c4867c3a80  A [1]: 0x55c4867c39f0
// 0x55c4867d23c0  A [1]: 0x55c4867c0170
// 0x55c4867d23c0  A [1]: 0x55c4867c0190
// ----------------------------------------
// ----------------------------------------
// 0x55c4867d23c0  A [1]: 0x55c4867b9c90
// 0x55c4867d23c0  A [1]: 0x55c4867b9cb0
// 0x55c4867d23c0  D [1]: 0x55c4867c0170
// 0x55c4867d23c0  D [1]: 0x55c4867c0190
// 0x55c4867d23c0  D [1]: 0x55c4867b9c90
// 0x55c4867d23c0  D [1]: 0x55c4867b9cb0
// 0x55c4867c3a80  D [1]: 0x55c4867c3a10
// 0x55c4867c3a80  D [1]: 0x55c4867c39f0