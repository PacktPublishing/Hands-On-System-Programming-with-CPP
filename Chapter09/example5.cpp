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
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

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

// 0x7ffce60fbd10 constructor, sizeof(T): 24
// 0x561feb431590  A [1]: 0x561feb43fec0
// 0x561feb431590  D [1]: 0x561feb43fec0

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

// 0x7ffc766ec580 constructor, sizeof(T): 24
// 0x7ffc766ec5b0 constructor, sizeof(T): 24
// 0x5638419d9720  A [1]: 0x5638419d0b60
// 0x5638419d9720  A [1]: 0x5638419de660
// 0x5638419e8060  A [1]: 0x5638419e0cf0
// 0x5638419e8060  A [1]: 0x5638419d9690
// ----------------------------------------
// 0x5638419e8060  D [1]: 0x5638419e0cf0
// 0x5638419e8060  D [1]: 0x5638419d9690
// 0x7ffc766ec5b0 copy assignment, sizeof(T): 24
// 0x7ffc766ec450 copy constructor (U), sizeof(T): 4
// 0x7ffc766ec3f0 copy constructor (U), sizeof(T): 24
// 0x7ffc766ec460 copy constructor, sizeof(T): 24
// 0x5638419d9720  A [1]: 0x5638419e8050
// 0x5638419d9720  A [1]: 0x5638419d9690
// ----------------------------------------
// 0x5638419d9720  A [1]: 0x5638419d96b0
// 0x5638419d9720  A [1]: 0x5638419d5e10
// 0x5638419d9720  D [1]: 0x5638419e8050
// 0x5638419d9720  D [1]: 0x5638419d9690
// 0x5638419d9720  D [1]: 0x5638419d96b0
// 0x5638419d9720  D [1]: 0x5638419d5e10
// 0x5638419d9720  D [1]: 0x5638419d0b60
// 0x5638419d9720  D [1]: 0x5638419de660

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

// 0x7ffc766ec580 constructor, sizeof(T): 24
// 0x7ffc766ec5b0 constructor, sizeof(T): 24
// 0x5638419d9720  A [1]: 0x5638419d96b0
// 0x5638419d9720  A [1]: 0x5638419d9690
// 0x5638419d5e20  A [1]: 0x5638419e8050
// 0x5638419d5e20  A [1]: 0x5638419d5e30
// ----------------------------------------
// 0x5638419d5e20  D [1]: 0x5638419e8050
// 0x5638419d5e20  D [1]: 0x5638419d5e30
// 0x7ffc766ec5b0 move assignment, sizeof(T): 24
// ----------------------------------------
// 0x5638419d9720  A [1]: 0x5638419d5e10
// 0x5638419d9720  A [1]: 0x5638419e8050
// 0x5638419d9720  D [1]: 0x5638419d96b0
// 0x5638419d9720  D [1]: 0x5638419d9690
// 0x5638419d9720  D [1]: 0x5638419d5e10
// 0x5638419d9720  D [1]: 0x5638419e8050