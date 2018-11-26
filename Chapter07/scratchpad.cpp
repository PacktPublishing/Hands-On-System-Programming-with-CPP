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

#if SNIPPET00

#include <iostream>

int bss_mem = 0;
int data_mem = 42;

int main()
{
    std::cout << bss_mem << '\n';
    std::cout << data_mem << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0
// 42

#endif

#if SNIPPET01

#include <iostream>

int main()
{
    int stack_mem = 42;
    std::cout << stack_mem << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET02

#include <iostream>

int main()
{
    int stack_mem[0x10000000];
    std::cout << stack_mem[0] << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// Segmentation fault (core dumped)

#endif

#if SNIPPET03

#include <iostream>

int main()
{
    auto ptr = new int;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5639c77e4e70

#endif

#if SNIPPET04

#include <iostream>

int main()
{
    auto ptr = new int[42];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5594a7d47e70

#endif

#if SNIPPET05

#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "my delete\n";
    }
};

int main()
{
    auto ptr = new myclass[2];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x56171064ae78
// my delete
// my delete

#endif

#if SNIPPET06

#include <iostream>

alignas(0x1000) int ptr[42];

int main()
{
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x560809897000

#endif

#if SNIPPET07

#include <iostream>

int main()
{
    alignas(0x1000) int ptr[42];
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x560809897000

#endif

#if SNIPPET08

#include <iostream>

int main()
{
    char buffer[0x2000];
    auto ptr1 = reinterpret_cast<uintptr_t>(buffer);
    auto ptr2 = ptr1 - (ptr1 % 0x1000) + 0x1000;

    std::cout << std::hex << std::showbase;
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7ffd160dec20
// 0x7ffd160df000

#endif

#if SNIPPET09

#include <iostream>

int main()
{
    int *ptr;

    if (posix_memalign(reinterpret_cast<void **>(&ptr), 0x1000, 42 * sizeof(int))) {
        std::clog << "ERROR: unable to allocate aligned memory\n";
        ::exit(EXIT_FAILURE);
    }

    std::cout << ptr << '\n';
    free(ptr);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55c5d31d1000

#endif

#if SNIPPET10

#include <iostream>

int main()
{
    if (auto ptr = aligned_alloc(0x1000, 42 * sizeof(int))) {
        std::cout << ptr << '\n';
        free(ptr);
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55c5d31d1000

#endif

#if SNIPPET11

#include <iostream>

using aligned_int alignas(0x1000) = int;

int main()
{
    auto ptr = new aligned_int;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55e32ece1000

#endif

#if SNIPPET12

#include <iostream>

using aligned_int alignas(0x1000) = int;

int main()
{
    auto ptr = new aligned_int[42];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5649c0597000

#endif

#if SNIPPET13

#include <iostream>

int main()
{
    auto ptr = new (std::nothrow) int;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55893e230e70

#endif

#if SNIPPET14

#include <iostream>

int main()
{
    auto ptr = new (std::nothrow) int[42];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5623076e9e70

#endif

#if SNIPPET15

#include <iostream>

using aligned_int alignas(0x1000) = int;

int main()
{
    auto ptr = new (std::nothrow) aligned_int;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55e36201a000

#endif

#if SNIPPET16

#include <iostream>

using aligned_int alignas(0x1000) = int;

int main()
{
    auto ptr = new (std::nothrow) aligned_int[42];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x557222103000

#endif

#if SNIPPET17

#include <iostream>

class myclass
{
public:
    myclass()
    {
        throw std::runtime_error("the answer was not 42");
    }
};

int main()
{
    auto ptr = new (std::nothrow) myclass;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// terminate called after throwing an instance of 'std::runtime_error'
// what(): the answer was not 42
// Aborted (core dumped)

#endif

#if SNIPPET18

#include <iostream>

char buf[0x1000];

int main()
{
    auto ptr = new (buf) int;
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5567b8884000

#endif

#if SNIPPET19

#include <iostream>

char buf[0x1000];

int main()
{
    auto ptr1 = new (buf) int;
    auto ptr2 = new (buf) int;
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x558044c66180
// 0x558044c66180

#endif

#if SNIPPET20

#include <iostream>

char buf[0x1000];

int main()
{
    auto ptr = new (buf) int[42];
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55594aff0000

#endif

#if SNIPPET21

#include <iostream>

alignas(0x1000) char buf[0x1000];

int main()
{
    auto ptr = new (buf) int;
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5567b8884000

#endif

#if SNIPPET22

#include <iostream>

alignas(0x1000) char buf[0x1000];

int main()
{
    auto ptr = new (buf) int[42];
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55594aff0000

#endif

#if SNIPPET23

#include <iostream>

void *operator new (std::size_t count)
{
    // WARNING: Do not use std::cout here
    return malloc(count);
}

void operator delete (void *ptr)
{
    // WARNING: Do not use std::cout here
    return free(ptr);
}

int main()
{
    auto ptr = new int;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55f204617e70

#endif

#if SNIPPET24

#include <iostream>

void *operator new[](std::size_t count)
{
    // WARNING: Do not use std::cout here
    return malloc(count);
}

void operator delete[](void *ptr)
{
    // WARNING: Do not use std::cout here
    return free(ptr);
}

int main()
{
    auto ptr = new int[42];
    std::cout << ptr << '\n';
    delete [] ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55e5e2c62e70

#endif

#if SNIPPET25

#include <iostream>

std::size_t allocations = 0;

void *operator new (std::size_t count)
{
    if (count >= 0x1000) {
        allocations++;
    }

    return malloc(count);
}

void operator delete (void *ptr)
{
    return free(ptr);
}

int main()
{
    auto ptr = new int;
    std::cout << allocations << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0

#endif

#if SNIPPET26

#include <iostream>

std::size_t allocations = 0;

void *operator new (std::size_t count)
{
    if (count >= 0x1000) {
        allocations++;
    }

    return malloc(count);
}

void operator delete (void *ptr)
{
    return free(ptr);
}

struct mystruct
{
    char buf[0x1000];
};

int main()
{
    auto ptr = new mystruct;
    std::cout << allocations << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 1

#endif

#if SNIPPET27

#include <iostream>

class myclass
{
public:
    void *operator new (std::size_t count)
    {
        std::cout << "my new\n";
        return ::operator new (count);
    }

    void operator delete (void *ptr)
    {
        std::cout << "my delete\n";
        return ::operator delete (ptr);
    }
};

int main()
{
    auto ptr = new myclass;
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// my new
// 0x5561cac52280
// my delete

#endif

#if SNIPPET28

#include <iostream>

class myclass
{
public:
    void *operator new[](std::size_t count, std::align_val_t al)
    {
        std::cout << "my new\n";
        return ::operator new (count, al);
    }

    void operator delete[](void *ptr, std::align_val_t al)
    {
        std::cout << "my delete\n";
        return ::operator delete (ptr, al);
    }
};

using aligned_myclass alignas(0x1000) = myclass;

int main()
{
    auto ptr1 = new aligned_myclass;
    auto ptr2 = new aligned_myclass[42];
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';
    delete ptr1;
    delete [] ptr2;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// my new
// 0x563b49b74000
// 0x563b49b76000
// my delete

#endif

// -----------------------------------------------------------------------------
// Section: Smart Pointers and Ownership
// -----------------------------------------------------------------------------

#if SNIPPET29

#include <iostream>

int main()
{
    auto ptr = new int;
    std::cout << ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; valgrind ./a.out
// ==8627== LEAK SUMMARY:
// ==8627== definitely lost: 4 bytes in 1 blocks
// ==8627== indirectly lost: 0 bytes in 0 blocks
// ==8627== possibly lost: 0 bytes in 0 blocks
// ==8627== still reachable: 0 bytes in 0 blocks
// ==8627== suppressed: 0 bytes in 0 blocks
// ==8627== Rerun with --leak-check=full to see details of leaked memory

#endif

#if SNIPPET30

#include <iostream>

int main()
{
    auto ptr = new int[42];
    std::cout << ptr << '\n';
    delete ptr;
}

// > g++ -std=c++17 scratchpad.cpp; valgrind ./a.out
// ==8656== Mismatched free() / delete / delete []
// ==8656== at 0x4C2E60B: operator delete(void*) (vg_replace_malloc.c:576)
// ==8656== by 0x108960: main (in /home/user/examples/chapter_7/a.out)
// ==8656== Address 0x5aebc80 is 0 bytes inside a block of size 168 alloc'd
// ==8656== at 0x4C2DC6F: operator new[](unsigned long) (vg_replace_malloc.c:423)
// ==8656== by 0x10892B: main (in /home/user/examples/chapter_7/a.out)

#endif

#if SNIPPET31

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int>(42);
    std::cout << *ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET32

#include <memory>
#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "my delete\n";
    }
};

int main()
{
    auto ptr = std::make_unique<myclass>();
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5621eb029e70
// my delete

#endif

#if SNIPPET33

#include <memory>
#include <iostream>

class myclass1
{
public:
    ~myclass1()
    {
        std::cout << "my delete\n";
    }
};

class myclass2
{
    std::unique_ptr<myclass1> m_data;

public:
    myclass2() :
        m_data{std::make_unique<myclass1>()}
    { }
};

int main()
{
    myclass2();
    std::cout << "complete\n";
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// my delete
// complete

#endif

#if SNIPPET34

#include <memory>
#include <iostream>

class myclass1
{
public:
    ~myclass1()
    {
        std::cout << "my delete\n";
    }
};

int main()
{
    std::unique_ptr<myclass1[]>(new myclass1[2]);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// my delete
// my delete

#endif

#if SNIPPET35

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int[]>(42);
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55b25f224e70
// my delete

#endif

#if SNIPPET36

#include <memory>
#include <iostream>

class int_deleter
{
public:
    void operator()(int *ptr) const
    {
        std::cout << "my delete\n";
        delete ptr;
    };
};

int main()
{
    auto ptr = std::unique_ptr<int, int_deleter>(new int, int_deleter());
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5615be977e70
// my delete

#endif

#if SNIPPET37

#include <memory>
#include <iostream>

using aligned_int alignas(0x1000) = int;

int main()
{
    auto ptr = std::unique_ptr<int>(new aligned_int);
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x560eb6a0a000

#endif

#if SNIPPET38

#include <memory>
#include <iostream>

struct mystruct {
    int data{42};
};

int main()
{
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = std::make_unique<mystruct>();
    std::cout << *ptr1 << '\n';
    std::cout << ptr2->data << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42
// 42

#endif

#if SNIPPET39

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int>();
    std::cout << ptr.get() << '\n';
    ptr.reset();
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55bcfa2b1e70
// 0

#endif

#if SNIPPET40

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int>(42);
    if (ptr) {
        std::cout << *ptr << '\n';
    }
    ptr.reset();
    if (ptr) {
        std::cout << *ptr << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET41

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int[]>(42);
    std::cout << ptr[0] << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0

#endif

#if SNIPPET42

#include <memory>
#include <iostream>

template<typename T> std::ostream &
operator<<(std::ostream &os, const std::unique_ptr<T> &ptr)
{
    os << ptr.get();
    return os;
}

int main()
{
    auto ptr = std::make_unique<int>();
    std::cout << ptr << '\n';
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x55ed70997e70

#endif

#if SNIPPET43

#include <thread>
#include <iostream>

class myclass
{
    int m_data{0};

public:

    ~myclass()
    {
        std::cout << "myclass deleted\n";
    }

    void inc()
    { m_data++; }
};

std::thread t1;
std::thread t2;

void
thread2(myclass *ptr)
{
    for (auto i = 0; i < 100000; i++) {
        ptr->inc();
    }

    std::cout << "thread2: complete\n";
}

void
thread1()
{
    auto ptr = std::make_unique<myclass>();
    t2 = std::thread(thread2, ptr.get());

    for (auto i = 0; i < 10; i++) {
        ptr->inc();
    }

    std::cout << "thread1: complete\n";
}

int main()
{
    t1 = std::thread(thread1);

    t1.join();
    t2.join();
}

// > g++ -std=c++17 -lpthread scratchpad.cpp; ./a.out
// thread1: complete
// myclass deleted
// thread2: complete

#endif

#if SNIPPET44

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_shared<int>();
    std::cout << ptr.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x562e6ba9ce80

#endif

#if SNIPPET45

#include <thread>
#include <iostream>

class myclass
{
    int m_data{0};

public:

    ~myclass()
    {
        std::cout << "myclass deleted\n";
    }

    void inc()
    { m_data++; }
};

std::thread t1;
std::thread t2;

void
thread2(const std::shared_ptr<myclass> ptr)
{
    for (auto i = 0; i < 100000; i++) {
        ptr->inc();
    }

    std::cout << "thread2: complete\n";
}

void
thread1()
{
    auto ptr = std::make_shared<myclass>();
    t2 = std::thread(thread2, ptr);

    for (auto i = 0; i < 10; i++) {
        ptr->inc();
    }

    std::cout << "thread1: complete\n";
}

int main()
{
    t1 = std::thread(thread1);

    t1.join();
    t2.join();
}

// > g++ -std=c++17 -lpthread scratchpad.cpp; ./a.out
// thread1: complete
// thread2: complete
// myclass deleted

#endif

#if SNIPPET46

#include <memory>
#include <iostream>

int main()
{
    auto ptr1 = std::make_shared<int>();
    auto ptr2 = ptr1;
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';
    ptr2.reset();
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x555b99574e80
// 0x555b99574e80
// 0x555b99574e80
// 0

#endif

#if SNIPPET47

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::shared_ptr<int>(new int[42]());
    std::cout << ptr.get()[0] << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0

#endif

#if SNIPPET48

#include <memory>
#include <iostream>

int main()
{
    auto ptr1 = std::make_shared<int>();
    auto ptr2 = ptr1;
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';
    std::cout << ptr1.use_count() << '\n';
    ptr2.reset();
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';
    std::cout << ptr1.use_count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x5644edde7e80
// 0x5644edde7e80
// 2
// 0x5644edde7e80
// 0
// 1

#endif

#if SNIPPET49

#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_shared<int>();
    if (ptr) {
        std::cout << "before: " << ptr.get() << '\n';
    }
    ptr.reset();
    if (ptr) {
        std::cout << "after: "<< ptr.get() << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// before: 0x55ac226b5e80

#endif

#if SNIPPET50

#include <memory>
#include <iostream>

struct mystruct {
    int data;
};

int main()
{
    auto ptr = std::make_shared<mystruct>();
    std::cout << ptr->data << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0

#endif

#if SNIPPET51

#include <memory>
#include <iostream>

class myclass2;

class myclass1
{
public:

    ~myclass1()
    {
        std::cout << "delete myclass1\n";
    }

    std::shared_ptr<myclass2> m;
};

class myclass2
{
public:

    ~myclass2()
    {
        std::cout << "delete myclass2\n";
    }

    std::shared_ptr<myclass1> m;
};

int main()
{
    auto ptr1 = std::make_shared<myclass1>();
    auto ptr2 = std::make_shared<myclass2>();
    ptr1->m = ptr2;
    ptr2->m = ptr1;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out

#endif

#if SNIPPET52

#include <memory>
#include <iostream>

class myclass2;

class myclass1
{
public:

    ~myclass1()
    {
        std::cout << "delete myclass1\n";
    }

    std::weak_ptr<myclass2> m;
};

class myclass2
{
public:

    ~myclass2()
    {
        std::cout << "delete myclass2\n";
    }

    std::weak_ptr<myclass1> m;
};

int main()
{
    auto ptr1 = std::make_shared<myclass1>();
    auto ptr2 = std::make_shared<myclass2>();
    ptr1->m = ptr2;
    ptr2->m = ptr1;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// delete myclass2
// delete myclass1

#endif

// -----------------------------------------------------------------------------
// Section: Mapping and Permissions
// -----------------------------------------------------------------------------

#if SNIPPET53

#include <iostream>
#include <sys/mman.h>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

int main()
{
    auto ptr = mmap(0, 0x1000, PROT_RW, MAP_ALLOC, -1, 0);
    std::cout << ptr << '\n';

    munmap(ptr, 0x1000);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7feb41ab6000

#endif

#if SNIPPET54

#include <iostream>
#include <sys/mman.h>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

int main()
{
    auto ptr1 = mmap(0, 42, PROT_RW, MAP_ALLOC, -1, 0);
    auto ptr2 = mmap(0, 42, PROT_RW, MAP_ALLOC, -1, 0);

    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';

    munmap(ptr1, 42);
    munmap(ptr2, 42);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7fc1637ad000
// 0x7fc1637ac000

#endif

#if SNIPPET55

#include <iostream>
#include <sys/mman.h>

constexpr auto PROT_RE = PROT_READ | PROT_EXEC;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

int main()
{
    auto ptr = mmap(0, 0x1000, PROT_RE, MAP_ALLOC, -1, 0);
    std::cout << ptr << '\n';

    munmap(ptr, 0x1000);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7feb41ab6000

#endif

#if SNIPPET56

#include <iostream>
#include <sys/mman.h>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

int main()
{
    auto ptr = mmap(0, 0x1000, PROT_RW, MAP_ALLOC, -1, 0);
    std::cout << ptr << '\n';

    if (mprotect(ptr, 0x1000, PROT_READ) == -1) {
        std::clog << "ERROR: Failed to change memory permissions\n";
        ::exit(EXIT_FAILURE);
    }

    munmap(ptr, 0x1000);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 0x7fb05b4b6000

#endif

#if SNIPPET57

#include <memory>
#include <iostream>

#include <string.h>
#include <sys/mman.h>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

class mmap_deleter
{
    std::size_t m_size;

public:
    mmap_deleter(std::size_t size) :
        m_size{size}
    { }

    void operator()(int *ptr) const
    {
        munmap(ptr, m_size);
    }
};

template<typename T, typename... Args>
auto mmap_unique(Args&&... args)
{
    if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_ALLOC, -1, 0)) {

        auto obj = new (ptr) T(args...);
        auto del = mmap_deleter(sizeof(T));

        return std::unique_ptr<T, mmap_deleter>(obj, del);
    }

    throw std::bad_alloc();
}

int main()
{
    auto ptr = mmap_unique<int>(42);
    std::cout << *ptr << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42

#endif

#if SNIPPET58

#include <memory>
#include <iostream>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;

auto name = "/shm";

class mmap_deleter
{
    std::size_t m_size;

public:
    mmap_deleter(std::size_t size) :
        m_size{size}
    { }

    void operator()(int *ptr) const
    {
        munmap(ptr, m_size);
    }
};

template<typename T, typename... Args>
auto mmap_unique_server(Args&&... args)
{
  if(int fd = shm_open(name, O_CREAT | O_RDWR, 0644); fd != -1) {
      ftruncate(fd, sizeof(T));

        if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_SHARED, fd, 0)) {

            auto obj = new (ptr) T(args...);
            auto del = mmap_deleter(sizeof(T));

            return std::unique_ptr<T, mmap_deleter>(obj, del);
        }
    }

    throw std::bad_alloc();
}

template<typename T>
auto mmap_unique_client()
{
  if(int fd = shm_open(name, O_RDWR, 0644); fd != -1) {
      ftruncate(fd, sizeof(T));

        if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_SHARED, fd, 0)) {

            auto obj = static_cast<T*>(ptr);
            auto del = mmap_deleter(sizeof(T));

            return std::unique_ptr<T, mmap_deleter>(obj, del);
        }
    }

    throw std::bad_alloc();
}

int main()
{
    auto ptr1 = mmap_unique_server<int>(42);
    auto ptr2 = mmap_unique_client<int>();
    std::cout << *ptr1 << '\n';
    std::cout << *ptr2 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// 42
// 42

#endif
