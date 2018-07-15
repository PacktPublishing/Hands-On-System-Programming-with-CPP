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

#if SNIPPET01

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);
    std::cout << "time: " << t << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 1531603643

#endif

#if SNIPPET02

#include <time.h>
#include <iostream>

int main()
{
    time_t t;
    time(&t);
    std::cout << "time: " << t << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 1531603652

#endif

#if SNIPPET03

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);
    std::cout << "time: " << ctime(&t);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 15:27:44 2018

#endif

#if SNIPPET05

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);
    std::cout << "time: " << asctime(localtime(&t));
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 15:28:59 2018

#endif

#if SNIPPET06

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);
    std::cout << "time: " << asctime(gmtime(&t));
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 21:46:12 2018

#endif

#if SNIPPET07

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);

    char buf[256]{};
    strftime(buf, sizeof(buf), "%m/%d/%Y", localtime(&t));

    std::cout << "time: " << buf << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 07/14/2018

#endif

#if SNIPPET08

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);

    char buf[256]{};
    strftime(buf, sizeof(buf), "%H:%M", localtime(&t));

    std::cout << "time: " << buf << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 15:41

#endif

#if SNIPPET09

#include <time.h>
#include <iostream>

int main()
{
    auto t = time(nullptr);

    char buf[256]{};
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Y", localtime(&t));

    std::cout << "time: " << buf << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 15:44:57 2018

#endif

#if SNIPPET10

#include <time.h>
#include <iostream>

#include <unistd.h>

int main()
{
    auto t1 = time(nullptr);
    sleep(2);
    auto t2 = time(nullptr);

    std::cout << "diff: " << difftime(t2, t1) << '\n';
    std::cout << "diff: " << t2 - t1 << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// diff: 2

#endif

#if SNIPPET11

#include <time.h>
#include <iostream>

int main()
{
    auto t1 = time(nullptr);
    auto lt = localtime(&t1);
    auto t2 = mktime(lt);

    std::cout << "time: " << ctime(&t2);
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 16:00:13 2018

#endif

#if SNIPPET12

#include <time.h>
#include <iostream>

int main()
{
    std::cout << "clock: " << clock() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// clock: 2002

#endif

#if SNIPPET13

#include <time.h>
#include <iostream>

#include <unistd.h>

int main()
{
    auto c1 = clock();
    sleep(2);
    auto c2 = clock();

    std::cout << "clock: " << (1000.0 * (c2 - c1)) / CLOCKS_PER_SEC << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// clock: 0.038

#endif

#if SNIPPET04

#include <time.h>
#include <iostream>

#include <unistd.h>

int main()
{
    auto c1 = clock();

    auto t1 = time(nullptr);
    while(time(nullptr) - t1 <= 2);

    auto c2 = clock();

    std::cout << "clock: " << (c2 - c1) / CLOCKS_PER_SEC << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// clock: 2

#endif

#if SNIPPET14

#include <chrono>
#include <iostream>

int main()
{
    auto t = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::system_clock::to_time_t(t) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 1531606644

#endif

#if SNIPPET15

#include <chrono>
#include <iostream>

template<typename C, typename D>
std::ostream &
operator<<(std::ostream &os, std::chrono::time_point<C,D> &obj)
{
    auto t = std::chrono::system_clock::to_time_t(obj);
    return os << ctime(&t);
}

int main()
{
    auto now = std::chrono::system_clock::now();
    std::cout << "time: " << now;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: Sat Jul 14 19:01:55 2018

#endif

#if SNIPPET16

#include <chrono>
#include <iostream>

using namespace std::chrono;

template<typename C, typename D>
std::ostream &
operator<<(std::ostream &os, std::chrono::time_point<C,D> &obj)
{
    auto t = std::chrono::system_clock::to_time_t(obj);
    return os << ctime(&t);
}

int main()
{
    auto now = std::chrono::system_clock::now();

    std::cout << "time: " << now;

    now += 1h;
    std::cout << "time: " << now;

    now -= 1h;
    std::cout << "time: " << now;
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 1531606644

#endif

#if SNIPPET17

#include <chrono>
#include <iostream>

int main()
{
    auto now1 = std::chrono::system_clock::now();
    auto now2 = std::chrono::system_clock::now();

    std::cout << std::boolalpha;
    std::cout << "compare: " << (now1 < now2) << '\n';
    std::cout << "compare: " << (now1 > now2) << '\n';
    std::cout << "compare: " << (now1 <= now2) << '\n';
    std::cout << "compare: " << (now1 >= now2) << '\n';
    std::cout << "compare: " << (now1 == now2) << '\n';
    std::cout << "compare: " << (now1 != now2) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// compare: true
// compare: false
// compare: true
// compare: false
// compare: false
// compare: true

#endif

#if SNIPPET18

#include <chrono>
#include <iostream>

#include <unistd.h>

int main()
{
    using namespace std::chrono;

    auto now1 = system_clock::now();
    sleep(2);
    auto now2 = system_clock::now();

    std::cout << "time: " <<
        duration_cast<seconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<milliseconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<nanoseconds>(now2 - now1).count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 2
// time: 2001
// time: 2001415132

#endif

#if SNIPPET19

#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;

    seconds t(42);

    t++;
    std::cout << "time: " << t.count() << '\n';

    t--;
    std::cout << "time: " << t.count() << '\n';

    t += 1s;
    std::cout << "time: " << t.count() << '\n';

    t -= 1s;
    std::cout << "time: " << t.count() << '\n';

    t %= 2s;
    std::cout << "time: " << t.count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 43
// time: 42
// time: 43
// time: 42
// time: 0

#endif

#if SNIPPET21

#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;

    auto t1 = 0s;
    auto t2 = 42s;

    std::cout << std::boolalpha;
    std::cout << "compare: " << (t1 < t2) << '\n';
    std::cout << "compare: " << (t1 > t2) << '\n';
    std::cout << "compare: " << (t1 <= t2) << '\n';
    std::cout << "compare: " << (t1 >= t2) << '\n';
    std::cout << "compare: " << (t1 == t2) << '\n';
    std::cout << "compare: " << (t1 != t2) << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// compare: true
// compare: false
// compare: true
// compare: false
// compare: false
// compare: true

#endif

#if SNIPPET22

#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;

    auto s1 = -42001ms;

    std::cout << "floor: " << floor<seconds>(s1).count() << '\n';
    std::cout << "ceil: " << ceil<seconds>(s1).count() << '\n';
    std::cout << "round: " << round<seconds>(s1).count() << '\n';
    std::cout << "abs: " << abs(s1).count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// floor: -43
// ceil: -42
// round: -42
// abs: 42001

#endif

#if SNIPPET23

#include <chrono>
#include <iostream>

#include <unistd.h>

int main()
{
    using namespace std::chrono;

    auto now1 = steady_clock::now();
    sleep(2);
    auto now2 = steady_clock::now();

    std::cout << "time: " <<
        duration_cast<seconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<milliseconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<nanoseconds>(now2 - now1).count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 2
// time: 2001
// time: 2001447628

#endif

#if SNIPPET24

#include <chrono>
#include <iostream>

#include <unistd.h>

int main()
{
    using namespace std::chrono;

    auto now1 = high_resolution_clock::now();
    sleep(2);
    auto now2 = high_resolution_clock::now();

    std::cout << "time: " <<
        duration_cast<seconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<milliseconds>(now2 - now1).count() << '\n';

    std::cout << "time: " <<
        duration_cast<nanoseconds>(now2 - now1).count() << '\n';
}

// > g++ -std=c++17 scratchpad.cpp; ./a.out
// time: 2
// time: 2000
// time: 2002297281

#endif
