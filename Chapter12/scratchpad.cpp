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
// Section: POSIX Threads
// -----------------------------------------------------------------------------

#if SNIPPET01

#include <iostream>
#include <pthread.h>

void *mythread(void *ptr)
{
    std::cout << "Hello World\n";
    return nullptr;
}

main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, nullptr, mythread, nullptr);
    pthread_create(&thread2, nullptr, mythread, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World
// Hello World

#endif

#if SNIPPET02

#include <iostream>
#include <pthread.h>

void *mythread(void *ptr)
{
    std::cout << "thread id: " << pthread_self() << '\n';
    return nullptr;
}

main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, nullptr, mythread, nullptr);
    pthread_create(&thread2, nullptr, mythread, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// thread id: 140232513570560
// thread id: 140232505177856

#endif

#if SNIPPET03

#include <iostream>
#include <pthread.h>

void *mythread(void *ptr)
{
    (*reinterpret_cast<int *>(ptr))++;
    return ptr;
}

main()
{
    int in_value = 42;
    void *out_value = nullptr;

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, nullptr, mythread, &in_value);
    pthread_create(&thread2, nullptr, mythread, &in_value);

    pthread_join(thread1, &out_value);
    pthread_join(thread2, &out_value);

    std::cout << "value: " << *reinterpret_cast<int *>(out_value) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// 44

#endif

#if SNIPPET04

#include <iostream>
#include <pthread.h>

void *mythread(void *ptr)
{
    while(true) {
        std::clog << static_cast<char *>(ptr) << '\n';
        pthread_yield();
    }
}

main()
{
    char name1[9] = "thread 1";
    char name2[9] = "thread 2";

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, nullptr, mythread, name1);
    pthread_create(&thread2, nullptr, mythread, name2);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// thread 2
// thread 2
// thread 2
// thread 1
// thread 2
// thread 2
// thread 1
// thread 1
// thread 1

#endif

#if SNIPPET05

#include <iostream>

#include <unistd.h>
#include <pthread.h>

void *mythread(void *ptr)
{
    while (true) {
        sleep(1);
        std::cout << "hello world\n";
    }
}

main()
{
    pthread_t thread;
    pthread_create(&thread, nullptr, mythread, nullptr);
    pthread_join(thread, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// hello world
// hello world
// hello world

#endif

#if SNIPPET06

#include <array>
#include <iostream>
#include <pthread.h>

int count = 0;

void *mythread(void *ptr)
{
    count++;
}

main()
{
    while (true) {
        count = 0;
        for (auto i = 0; i < 1000; i++) {
            std::array<pthread_t, 8> threads;

            for (auto &t : threads) {
                pthread_create(&t, nullptr, mythread, nullptr);
            }

            for (auto &t : threads) {
                pthread_join(t, nullptr);
            }
        }

        std::cout << "count: " << count << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 7992
// count: 7996
// count: 7998
// count: 8000
// count: 8000

#endif

#if SNIPPET07

#include <array>
#include <iostream>
#include <pthread.h>

int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void *ptr)
{
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
}

main()
{
    while (true) {
        count = 0;
        for (auto i = 0; i < 1000; i++) {
            std::array<pthread_t, 8> threads;

            for (auto &t : threads) {
                pthread_create(&t, nullptr, mythread, nullptr);
            }

            for (auto &t : threads) {
                pthread_join(t, nullptr);
            }
        }

        std::cout << "count: " << count << '\n';
    }
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 8000
// count: 8000
// count: 8000
// count: 8000
// count: 8000

#endif

#if SNIPPET08

#include <iostream>
#include <pthread.h>

int count = 0;
pthread_mutex_t lock;
pthread_mutexattr_t attr;

void *mythread(void *ptr)
{
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);
}

main()
{
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock, &attr);

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, nullptr, mythread, nullptr);
    pthread_create(&thread2, nullptr, mythread, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET09

#include <iostream>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread1(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 1\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}

void *mythread2(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 2\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}

main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread2, nullptr, mythread2, nullptr);
    pthread_create(&thread1, nullptr, mythread1, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World: 2
// Hello World: 1

#endif

#if SNIPPET10

#include <iostream>
#include <pthread.h>

bool predicate = false;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread1(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 1\n";
    predicate = true;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);

    return nullptr;
}

void *mythread2(void *ptr)
{
    pthread_mutex_lock(&lock);
    while(!predicate) {
        pthread_cond_wait(&cond, &lock);
    }
    std::cout << "Hello World: 2\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}

main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread2, nullptr, mythread2, nullptr);
    pthread_create(&thread1, nullptr, mythread1, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World: 1
// Hello World: 2

#endif

// -----------------------------------------------------------------------------
// Section: C++ Threads
// -----------------------------------------------------------------------------

#if SNIPPET11

#include <thread>
#include <iostream>

void mythread()
{
    std::cout << "Hello World\n";
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World
// Hello World

#endif

#if SNIPPET12

#include <thread>
#include <iostream>

void mythread()
{
    std::cout << "thread id: " << std::this_thread::get_id() << '\n';
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    std::cout << "thread1 id: " << t1.get_id() << '\n';
    std::cout << "thread2 id: " << t2.get_id() << '\n';

    t1.join();
    t2.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// thread1 id: 139960486229760
// thread2 id: 139960477837056
// thread id: 139960477837056
// thread id: 139960486229760

#endif

#if SNIPPET13

#include <thread>
#include <future>
#include <iostream>

int mythread(int value)
{
    return ++value;
}

main()
{
    std::packaged_task<int(int)> task1(mythread);
    std::packaged_task<int(int)> task2(mythread);

    auto f1 = task1.get_future();
    auto f2 = task2.get_future();

    std::thread t1(std::move(task1), 42);
    std::thread t2(std::move(task2), 42);

    t1.join();
    t2.join();

    std::cout << "value1: " << f1.get() << '\n';
    std::cout << "value2: " << f2.get() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World
// Hello World

#endif

#if SNIPPET14

#include <thread>
#include <iostream>

void mythread(const char *str)
{
    while(true) {
        std::clog << str << '\n';
        std::this_thread::yield();
    }
}

main()
{
    std::thread t1{mythread, "thread 1"};
    std::thread t2{mythread, "thread 2"};

    t1.join();
    t2.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// thread 2
// thread 2
// thread 1
// thread 1
// thread 1
// thread 1
// thread 1
// thread 2
// thread 1

#endif

#if SNIPPET15

#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

void mythread()
{
    while (true) {
        std::this_thread::sleep_for(1s);
        std::cout << "hello world\n";
    }
}

main()
{
    std::thread t{mythread};
    t.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// hello world
// hello world
// hello world

#endif

#if SNIPPET16

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex;

void mythread()
{
    mutex.lock();
    count++;
    mutex.unlock();
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET17

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex;

void mythread()
{
    std::lock_guard lock(mutex);

    if (count == 1) {
        return;
    }

    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 1

#endif

#if SNIPPET18

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex;

void mythread()
{
    while(!mutex.try_lock());
    count++;
    mutex.unlock();
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET19

#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

int count = 0;
std::mutex mutex;

using namespace std::chrono_literals;

void mythread()
{
    std::unique_lock lock(mutex, std::defer_lock);

    while(!lock.try_lock()) {
        std::this_thread::sleep_for(1s);
    }

    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET20

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::recursive_mutex mutex;

void mythread()
{
    std::lock_guard lock1(mutex);
    std::lock_guard lock2(mutex);
    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET21

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex;

void mythread()
{
    std::lock_guard lock(mutex);
    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET22

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex1;
std::mutex mutex2;

void mythread()
{
    std::scoped_lock lock(mutex1, mutex2);
    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET23

#include <shared_mutex>
#include <thread>
#include <iostream>

int count = 0;
std::shared_mutex mutex;

void mythread1()
{
    while(true) {
        std::unique_lock lock(mutex);
        count++;
    }
}

void mythread2()
{
    while(true) {
        std::shared_lock lock(mutex);
        std::cout << "count: " << count << '\n';
    }
}

main()
{
    std::thread t1{mythread1};
    std::thread t2{mythread2};
    std::thread t3{mythread2};

    t1.join();
    t2.join();
    t3.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 999
// count: 1000
// count: 1000
// count: 1000
// count: 1000
// count: 1000
// count: count: 1000
// count: 1000

#endif

#if SNIPPET24

#include <mutex>
#include <thread>
#include <iostream>

int count = 0;
std::mutex mutex1;
std::mutex mutex2;

void mythread()
{
    std::unique_lock lock1(mutex1, std::defer_lock);
    std::unique_lock lock2(mutex2, std::defer_lock);

    std::lock(lock1, lock2);

    count++;
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();

    std::cout << "count: " << count << '\n';
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// count: 2

#endif

#if SNIPPET25

#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

std::mutex mutex;
std::condition_variable cond;

void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_one();
}

void mythread2()
{
    std::unique_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
}

main()
{
    std::thread t2{mythread2};
    std::thread t1{mythread1};

    t1.join();
    t2.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World: 1
// Hello World: 2

#endif

#if SNIPPET26

#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

std::mutex mutex;
std::condition_variable cond;

void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_all();
}

void mythread2()
{
    std::unique_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
    cond.notify_one();
}

main()
{
    std::thread t2{mythread2};
    std::thread t3{mythread2};
    std::thread t1{mythread1};

    t1.join();
    t2.join();
    t3.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World: 1
// Hello World: 2
// Hello World: 2

#endif

#if SNIPPET27

#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

std::shared_mutex mutex;
std::condition_variable_any cond;

void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_all();
}

void mythread2()
{
    std::shared_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
}

main()
{
    std::thread t2{mythread2};
    std::thread t3{mythread2};
    std::thread t1{mythread1};

    t1.join();
    t2.join();
    t3.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World: 1
// Hello World: 2
// Hello World: 2

#endif

#if SNIPPET28

#include <mutex>
#include <thread>
#include <iostream>

std::once_flag flag;

void mythread()
{
    std::call_once(flag, [] {
        std::cout << "Hello World\n";
    });
}

main()
{
    std::thread t1{mythread};
    std::thread t2{mythread};

    t1.join();
    t2.join();
}

// > g++ -std=c++17 scratchpad.cpp -lpthread; ./a.out
// Hello World

#endif
