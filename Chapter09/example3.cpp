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

#include <set>
#include <list>

#include <iostream>
#include <sys/mman.h>

#include <gsl/gsl>
using namespace gsl;

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

constexpr auto page_size = 0x1000;
constexpr auto pagepool_size = 255U;
constexpr auto objtpool_size = 255U;

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

struct __oa_page {
    gsl::byte data[page_size];
};

template<typename S>
S *__oa_alloc()
{
    static_assert(page_size == sizeof(S), "allocation is not a page");
    void *addr;

    if (GSL_LIKELY(addr = mmap(0, page_size, PROT_RW, MAP_ALLOC, -1, 0))) {
        return static_cast<S *>(std::memset(addr, 0, sizeof(S)));
    }

    throw std::runtime_error("__oa_alloc: out of memory");
}

template<typename S>
void __oa_free(S *ptr)
{
    static_assert(page_size == sizeof(S), "deallocation is not a page");
    munmap(ptr, page_size);
}

// -----------------------------------------------------------------------------
// Allocator Definition
// -----------------------------------------------------------------------------

template<typename T>
class object_allocator
{
    static_assert(page_size >= sizeof(T), "T is too large");

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
    using is_always_equal = std::false_type;

    template<typename U> struct rebind {
        using other = object_allocator<U>;
    };

public:

    object_allocator() noexcept
    { }

    ~object_allocator() noexcept
    {
        if (m_used_stack_top != nullptr) {
            std::clog << "object_allocator leaked memory\n";
            return;
        }

        cleanup();
    }

    object_allocator(object_allocator &&other) noexcept
    { *this = std::move(other); }

    object_allocator &operator=(object_allocator &&other) noexcept
    {
        if (GSL_UNLIKELY(this != &other)) {

            if (m_used_stack_top != nullptr) {
                std::clog << "object_allocator leaked memory\n";
            }
            else {
                cleanup();
            }

            m_free_stack_top = other.m_free_stack_top;
            m_used_stack_top = other.m_used_stack_top;
            m_page_stack_top = other.m_page_stack_top;
            m_objt_stack_top = other.m_objt_stack_top;

            other.m_free_stack_top = nullptr;
            other.m_used_stack_top = nullptr;
            other.m_page_stack_top = nullptr;
            other.m_objt_stack_top = nullptr;
        }

        return *this;
    }

    template <typename U>
    object_allocator(const object_allocator<U> &other) noexcept
    { (void) other; }

    object_allocator(const object_allocator &other) noexcept
    { (void) other; }

    object_allocator &operator=(const object_allocator &other) noexcept
    { (void) other; }

    pointer allocate(size_type n)
    {
        if (n != 1) {
            return new T[n];
        }

        auto objt = free_stack_pop();
        used_stack_push(objt);

        return static_cast<pointer>(objt->addr);
    }

    void deallocate(pointer p, size_type n)
    {
        if (n != 1) {
            return delete [] p;
        }

        auto objt = used_stack_pop();
        free_stack_push(objt);

        objt->addr = p;
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&... args)
    { ::new (reinterpret_cast<void *>(p)) U(std::forward<Args>(args)...); }

    template <typename U>
    void destroy(U *p)
    { p->~U(); }

public:

    inline bool contains(pointer p) const noexcept
    {
        auto next = m_page_stack_top;

        while (next != nullptr) {

            for (auto i = 0ULL; i < next->index; i++) {
                auto s = next->pool[i].addr;
                auto e = next->pool[i].addr + page_size;

                if (reinterpret_cast<gsl::byte *>(p) >= s &&
                    reinterpret_cast<gsl::byte *>(p) < e) {
                    return true;
                }
            }

            next = next->next;
        }

        return false;
    }

    inline size_type size(pointer ptr) const
    { (void) ptr; return sizeof(T); }

    inline size_type page_stack_size() noexcept
    {
        auto size = 0ULL;
        auto next = m_page_stack_top;

        while (next != nullptr) {
            ++size;
            next = next->next;
        }

        return size;
    }

    inline size_type objt_stack_size() noexcept
    {
        auto size = 0ULL;
        auto next = m_objt_stack_top;

        while (next != nullptr) {
            ++size;
            next = next->next;
        }

        return size;
    }

    inline size_type num_page() noexcept
    {
        auto size = 0ULL;
        auto next = m_page_stack_top;

        while (next != nullptr) {
            size += next->index;
            next = next->next;
        }

        return size;
    }

    inline size_type num_free() noexcept
    {
        auto size = 0ULL;
        auto next = m_free_stack_top;

        while (next != nullptr) {
            ++size;
            next = next->next;
        }

        return size;
    }

    inline size_type num_used() noexcept
    {
        auto size = 0ULL;
        auto next = m_used_stack_top;

        while (next != nullptr) {
            ++size;
            next = next->next;
        }

        return size;
    }

private:

    struct object_t {
        pointer addr;
        object_t *next;
    };

    struct object_stack_t {
        object_t pool[objtpool_size];

        uint64_t index;
        object_stack_t *next;
    };

    struct page_t {
        gsl::byte *addr;
        uint64_t index;
    };

    struct page_stack_t {
        page_t pool[pagepool_size];

        uint64_t index;
        page_stack_t *next;
    };

    object_t *m_free_stack_top{nullptr};
    object_t *m_used_stack_top{nullptr};

    page_stack_t *m_page_stack_top{nullptr};
    object_stack_t *m_objt_stack_top{nullptr};

private:

    inline page_t *get_next_page()
    {
        if (m_page_stack_top == nullptr ||
            m_page_stack_top->index == pagepool_size) {
            expand_page_stack();
        }

        auto page = &gsl::at(m_page_stack_top->pool, m_page_stack_top->index);
        page->addr = static_cast<gsl::byte *>(
            mmap(0, page_size, PROT_RW, MAP_ALLOC, -1, 0)
        );
        page->index = 0;

        ++m_page_stack_top->index;

        return page;
    }

    inline object_t *get_next_object()
    {
        if (m_objt_stack_top == nullptr ||
            m_objt_stack_top->index == objtpool_size) {
            expand_object_stack();
        }

        return &gsl::at(m_objt_stack_top->pool, m_objt_stack_top->index++);
    }

    inline void free_stack_push(object_t *next)
    {
        next->next = m_free_stack_top;
        m_free_stack_top = next;
    }

    inline object_t *free_stack_pop()
    {
        if (m_free_stack_top == nullptr) {
            add_to_free_stack();
        }

        auto top = m_free_stack_top;

        m_free_stack_top = m_free_stack_top->next;
        top->next = nullptr;

        return top;
    }

    inline void used_stack_push(object_t *next)
    {
        next->next = m_used_stack_top;
        m_used_stack_top = next;
    }

    inline object_t *used_stack_pop()
    {
        if (GSL_UNLIKELY(m_used_stack_top == nullptr)) {
            std::clog << "used_stack_pop empty. memory corruption likely\n";
            used_stack_push(get_next_object());
        }

        auto top = m_used_stack_top;

        m_used_stack_top = m_used_stack_top->next;
        top->next = nullptr;

        return top;
    }

    inline void expand_page_stack()
    {
        auto next = __oa_alloc<page_stack_t>();

        next->next = m_page_stack_top;
        m_page_stack_top = next;
    }

    inline void expand_object_stack()
    {
        auto next = __oa_alloc<object_stack_t>();

        next->next = m_objt_stack_top;
        m_objt_stack_top = next;
    }

    inline void add_to_free_stack()
    {
        auto page = get_next_page();

        for (auto i = 0ULL; i + sizeof(T) <= page_size; i += sizeof(T)) {
            auto object = get_next_object();
            free_stack_push(object);

            auto view = gsl::make_span(page->addr, page_size);
            object->addr = reinterpret_cast<pointer>(&view[i]);
        }
    }

    inline void cleanup() noexcept
    {
        while (m_page_stack_top != nullptr) {
            if (m_page_stack_top->index != 0) {
                for (auto i = 0ULL; i < m_page_stack_top->index; ++i) {
                    auto page = &gsl::at(m_page_stack_top->pool, i);
                    munmap(page->addr, page_size);
                }
            }

            auto next = m_page_stack_top->next;
            __oa_free<page_stack_t>(m_page_stack_top);
            m_page_stack_top = next;
        }

        while (m_objt_stack_top != nullptr) {
            auto next = m_objt_stack_top->next;
            __oa_free<object_stack_t>(m_objt_stack_top);
            m_objt_stack_top = next;
        }

        m_free_stack_top = nullptr;
        m_used_stack_top = nullptr;
        m_page_stack_top = nullptr;
        m_objt_stack_top = nullptr;
    }

private:

    template <typename T1, typename T2>
    friend bool operator==(const object_allocator<T1> &lhs, const object_allocator<T2> &rhs);

    template <typename T1, typename T2>
    friend bool operator!=(const object_allocator<T1> &lhs, const object_allocator<T2> &rhs);
};

template <typename T1, typename T2>
bool operator==(const object_allocator<T1> &, const object_allocator<T2> &)
{ return false; }

template <typename T1, typename T2>
bool operator!=(const object_allocator<T1> &, const object_allocator<T2> &)
{ return true; }

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

TEST_CASE("size / contains")
{
    std::cout << "size\n";
    std::cout << std::boolalpha;

    object_allocator<myclass> myalloc;

    auto ptr = myalloc.allocate(1);
    std::cout << myalloc.size(ptr) << '\n';
    std::cout << myalloc.contains(ptr) << '\n';
    myalloc.deallocate(ptr, 1);
}

TEST_CASE("stats single allocation")
{
    std::cout << "stats single allocation\n";

    object_allocator<myclass> myalloc;

    auto ptr = myalloc.allocate(1);
    std::cout << myalloc.page_stack_size() << '\n';
    std::cout << myalloc.objt_stack_size() << '\n';
    std::cout << myalloc.num_page() << '\n';
    std::cout << myalloc.num_free() << '\n';
    std::cout << myalloc.num_used() << '\n';
    myalloc.deallocate(ptr, 1);
}

TEST_CASE("stats multiple allocations")
{
    std::cout << "stats multiple allocations\n";

    std::set<myclass *> ptrs;
    object_allocator<myclass> myalloc;

    for (auto i = 0; i < 0x10000; i++) {
        ptrs.insert(myalloc.allocate(1));
    }

    std::cout << myalloc.page_stack_size() << '\n';
    std::cout << myalloc.objt_stack_size() << '\n';
    std::cout << myalloc.num_page() << '\n';
    std::cout << myalloc.num_free() << '\n';
    std::cout << myalloc.num_used() << '\n';

    for (const auto &ptr : ptrs) {
        myalloc.deallocate(ptr, 1);
    }
}

TEST_CASE("no deallocate")
{
    std::cout << "no deallocate\n";

    object_allocator<myclass> myalloc;
    auto ptr = myalloc.allocate(1);
}
