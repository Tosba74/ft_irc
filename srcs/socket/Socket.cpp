#include "socket/Socket.hpp"

Socket::Socket(int sock): sock(sock)
{
}

Socket::Socket(int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP): sock(socket(AF_INET, type, proto))
{
    if (sock == -1)
        throw SocketException("Socket creation failed");
}

Socket::Socket(Socket const &src): sock(src.sock)
{
}

Socket &Socket::operator=(Socket const &rhs)
{
    this->sock = rhs.sock;
    return *this;
}

Socket::~Socket()
{
    this->close();
}

int Socket::getSock()
{
    return this->sock;
}

void Socket::setSock(int sock)
{
    this->sock = sock;
}

void Socket::close()
{
    ::close(this->sock);
}