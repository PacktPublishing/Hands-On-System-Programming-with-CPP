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

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

// -----------------------------------------------------------------------------
// Allocator Definition
// -----------------------------------------------------------------------------

template<typename T>
class object_allocator
{
public:

    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using void_pointer = void *;
    using const_void_pointer = const void *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
    using is_always_equal = std::true_type;

    template<typename U> struct rebind {
        using other = object_allocator<U>;
    };

public:

    object_allocator() noexcept
    { }

    ~object_allocator() noexcept
    { }

    object_allocator(object_allocator &&other) noexcept
    { *this = std::move(other); }

    object_allocator &operator=(object_allocator &&other) noexcept
    { return *this; }

    template <typename U>
    object_allocator(const object_allocator<U> &other) noexcept
    { (void) other; }

    object_allocator(const object_allocator &other) noexcept
    { (void) other; }

    object_allocator &operator=(const object_allocator &other) noexcept
    { (void) other; }

    pointer allocate(size_type n)
    { return static_cast<pointer>(std::aligned_alloc(0x1000, sizeof(T) * n)); }

    void deallocate(pointer p, size_type n)
    { (void) n; free(p); }

    template <typename U, typename... Args>
    void construct(U *p, Args &&... args)
    { ::new (reinterpret_cast<void *>(p)) U(std::forward<Args>(args)...); }

    template <typename U>
    void destroy(U *p)
    { p->~U(); }

private:

    template <typename T1, typename T2>
    friend bool operator==(const object_allocator<T1> &lhs, const object_allocator<T2> &rhs);

    template <typename T1, typename T2>
    friend bool operator!=(const object_allocator<T1> &lhs, const object_allocator<T2> &rhs);
};

template <typename T1, typename T2>
bool operator==(const object_allocator<T1> &, const object_allocator<T2> &)
{ return true; }

template <typename T1, typename T2>
bool operator!=(const object_allocator<T1> &, const object_allocator<T2> &)
{ return false; }

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

struct myclass
{
    int data1;
    int data2;
};

TEST_CASE("constructor / destructor")
{
    std::cout << "constructor / destructor\n";

    object_allocator<myclass> myalloc;
}

TEST_CASE("allocate single object")
{
    std::cout << "allocate single object\n";

    object_allocator<myclass> myalloc;

    auto ptr = myalloc.allocate(1);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 1);
}

TEST_CASE("allocate multiple objects")
{
    std::cout << "allocate multiple objects\n";

    object_allocator<myclass> myalloc;

    auto ptr = myalloc.allocate(5);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 5);
}
