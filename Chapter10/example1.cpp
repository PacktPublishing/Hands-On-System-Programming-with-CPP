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
#define MAX_SIZE 0x10

#ifdef SERVER

#include <array>
#include <iostream>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

class myserver
{
    int m_fd{};
    struct sockaddr_in m_addr{};
    struct sockaddr_in m_client{};

public:
    myserver(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_DGRAM, 0); m_fd == -1) {
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

    ssize_t recv(std::array<char, MAX_SIZE> &buf)
    {
        socklen_t client_len = sizeof(m_client);

        return ::recvfrom(
            m_fd,
            buf.data(),
            buf.size(),
            0,
            (struct sockaddr *) &m_client,
            &client_len
        );
    }

    ssize_t send(std::array<char, MAX_SIZE> &buf, ssize_t len)
    {
        if (len >= buf.size()) {
            throw std::out_of_range("len >= buf.size()");
        }

        return ::sendto(
            m_fd,
            buf.data(),
            len,
            0,
            (struct sockaddr *) &m_client,
            sizeof(m_client)
        );
    }

    void echo()
    {
        while(true)
        {
            std::array<char, MAX_SIZE> buf{};

            if (auto len = recv(buf); len != 0) {
                send(buf, len);
            }
            else {
                break;
            }
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
    server.echo();
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
#include <iostream>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

class myclient
{
    int m_fd{};
    struct sockaddr_in m_addr{};

public:
    myclient(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_DGRAM, 0); m_fd == -1) {
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

    ssize_t recv(std::array<char, MAX_SIZE> &buf)
    {
        return ::recv(
            m_fd,
            buf.data(),
            buf.size() - 1,
            0
        );
    }

    void echo()
    {
        while(true) {
            std::string sendbuf{};
            std::array<char, MAX_SIZE> recvbuf{};

            std::cin >> sendbuf;
            if (sendbuf == "exit") {
                send({});
                break;
            }

            send(sendbuf);
            recv(recvbuf);

            std::cout << recvbuf.data() << '\n';
        }
    }

    ~myclient()
    {
        close(m_fd);
    }
};

int
protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    myclient client{PORT};
    client.echo();
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
