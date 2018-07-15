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

#include <stdint.h>

#define PORT 22000
#define MAX_SIZE 0x100

struct packet
{
    uint64_t data1;
    uint64_t data2;

    uint64_t len;
    char buf[MAX_SIZE];
};

#ifdef SERVER

#include <iostream>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

class myserver
{
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

    ~myserver()
    {
        close(m_fd);
    }

    int bind()
    {
        return ::bind(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr)
        );
    }

    ssize_t recv(packet &p)
    {
        return ::recv(
            m_client,
            &p,
            sizeof(p),
            0
        );
    }

    void recv_packet()
    {
        if (::listen(m_fd, 0) == -1) {
            throw std::runtime_error(strerror(errno));
        }

        if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1) {
            throw std::runtime_error(strerror(errno));
        }

        packet p{};

        if (auto len = recv(p); len != 0) {
            auto msg = std::string(p.buf, p.len);

            std::cout << "data1: " << p.data1 << '\n';
            std::cout << "data2: " << p.data2 << '\n';
            std::cout << "msg: \"" << msg << "\"\n";
            std::cout << "len: " << len << '\n';
        }

        close(m_client);
    }

private:

    int m_fd{};
    int m_client{};
    struct sockaddr_in m_addr{};
};

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    myserver server{PORT};
    server.recv_packet();
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

#include <string>
#include <iostream>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

class myclient
{
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

    ~myclient()
    {
        close(m_fd);
    }

    int connect()
    {
        return ::connect(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr)
        );
    }

    ssize_t send(const packet &p)
    {
        return ::send(
            m_fd,
            &p,
            sizeof(p),
            0
        );
    }

    void send_packet()
    {
        auto msg = std::string("Hello World");

        packet p = {
            42,
            43,
            msg.size(),
            {}
        };

        memcpy(p.buf, msg.data(), msg.size());

        send(p);
    }

private:

    int m_fd{};
    struct sockaddr_in m_addr{};
};


int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    myclient client{PORT};
    client.send_packet();
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
