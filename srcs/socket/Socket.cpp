#include "socket/Socket.hpp"

Socket::Socket(int sock): sock(sock)
{
}

Socket::Socket(int type, int opt, int proto): sock(socket(type, opt, proto))
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

int Socket::getSock() const
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