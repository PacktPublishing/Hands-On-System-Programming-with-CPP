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

#define PORT 22000
#define MAX_SIZE 0x1000

#ifdef SERVER

#include <array>
#include <unordered_map>

#include <sstream>
#include <fstream>
#include <iostream>

#include <mutex>
#include <thread>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

std::mutex log_mutex;
std::fstream g_log{"server_log.txt", std::ios::out | std::ios::app};

ssize_t
recv(int handle, std::array<char, MAX_SIZE> &buf)
{
    return ::recv(
        handle,
        buf.data(),
        buf.size(),
        0
    );
}

void
log(int handle)
{
    while(true)
    {
        std::array<char, MAX_SIZE> buf{};

        if (auto len = recv(handle, buf); len != 0) {
            std::unique_lock lock(log_mutex);

            g_log.write(buf.data(), len);
            std::clog.write(buf.data(), len);

            g_log.flush();
        }
        else {
            break;
        }
    }

    close(handle);
}

class myserver
{
    int m_fd{};
    struct sockaddr_in m_addr{};

public:

    myserver(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1) {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind() == -1) {
            throw std::runtime_error(strerror(errno));
        }
    }

    int bind()
    {
        return ::bind(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr)
        );
    }

    void listen()
    {
        if (::listen(m_fd, 0) == -1) {
            throw std::runtime_error(strerror(errno));
        }

        while (true) {
            if (int c = ::accept(m_fd, nullptr, nullptr); c != -1) {
                std::thread t{log, c};
                t.detach();

                continue;
            }

            throw std::runtime_error(strerror(errno));
        }
    }

    ~myserver()
    {
        close(m_fd);
    }
};

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    myserver server{PORT};
    server.listen();
}

int
main(int argc, char** argv)
{
    try {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}

#endif

#ifdef CLIENT

#include <array>
#include <string>

#include <sstream>
#include <fstream>
#include <iostream>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

class myclient
{
    int m_fd{};
    struct sockaddr_in m_addr{};

public:
    myclient(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1) {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if (connect() == -1) {
            throw std::runtime_error(strerror(errno));
        }
    }

    int connect()
    {
        return ::connect(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr)
        );
    }

    ssize_t send(const std::string &buf)
    {
        return ::send(
            m_fd,
            buf.data(),
            buf.size(),
            0
        );
    }

    ~myclient()
    {
        close(m_fd);
    }
};

myclient g_client{PORT};
std::fstream g_log{"client_log.txt", std::ios::out | std::ios::app};

template <std::size_t LEVEL>
constexpr void log(void(*func)()) {
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
        std::stringstream buf;

        auto g_buf = std::clog.rdbuf();
        std::clog.rdbuf(buf.rdbuf());

        func();

        std::clog.rdbuf(g_buf);

        std::clog << "\033[1;32mDEBUG\033[0m: ";
        std::clog << buf.str();

        g_log << "\033[1;32mDEBUG\033[0m: ";
        g_log << buf.str();

        g_client.send("\033[1;32mDEBUG\033[0m: ");
        g_client.send(buf.str());
    };
}

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    log<0>([]{
        std::clog << "Hello World\n";
    });

    std::clog << "Hello World\n";

    return EXIT_SUCCESS;
}

int
main(int argc, char** argv)
{
    try {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e) {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}

#endif