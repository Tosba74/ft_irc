#include "socket/SocketConnection.hpp"

SocketConnection::SocketConnection(int sock, sockaddr_in &addr) throw() : Socket(sock), addr(addr), addrsize(sizeof(addr))
{
}

SocketConnection::SocketConnection(SocketConnection const &src) throw() : Socket(src), addr(src.addr), addrsize(sizeof(src.addr))
{
}

SocketConnection &SocketConnection::operator=(SocketConnection const &rhs)
{
    this->addr = rhs.addr;
    this->addrsize = rhs.addrsize;
    this->writeBuffer = rhs.writeBuffer;
    this->readBuffer = rhs.readBuffer;
    this->addrsize = rhs.addrsize;
    return *this;
}

SocketConnection::~SocketConnection()
{
    this->flush();
    this->close();
    readBuffer.clear();
}

std::string SocketConnection::getAddr()
{
    return inet_ntoa(this->addr.sin_addr);
}

socklen_t SocketConnection::getAddrsize()
{
    return this->addrsize;
}

void SocketConnection::flush()
{
    if (this->writeBuffer.size() > 0)
    {
        ::write(this->sock, this->writeBuffer.c_str(), this->writeBuffer.size());
        this->writeBuffer.clear();
    }
}

int  SocketConnection::receive()
{
    char buffer[4096];
    int  n;

    n = ::read(this->sock, buffer, 4096);
    if (n > 0)
    {
        this->readBuffer += buffer;
    }
    return n;
}
SocketConnection &SocketConnection::operator<<(std::string const &msg)
{
    this->writeBuffer += msg;
    return *this;
}

SocketConnection &SocketConnection::operator>>(std::string &msg)
{
    msg = this->readBuffer;
    this->readBuffer.clear();
    return *this;
}

int SocketConnection::getPort()
{
    return ntohs(this->addr.sin_port);
}