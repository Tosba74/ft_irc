#include "socket/SocketListener.hpp"

SocketListener::~SocketListener() throw()
{
}

SocketListener::SocketListener(int type, int opt , int proto) throw() : Socket(type, opt, proto), listening(false)
{
}

void SocketListener::bind(std::string const& hostname, int service, int type)
{
    if (listening)
        throw SocketException("Socket already listening");
    if (hostname.empty())
        throw SocketException("Hostname is empty");
    if (this->sock == -1)
        throw SocketException("Socket creation failed");
    struct sockaddr_in addr;
    addr.sin_family = type;
    addr.sin_port = htons(service);
    addr.sin_addr.s_addr = inet_addr(hostname.c_str());
    if (::bind(this->sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw SocketException("Socket bind failed");
    std::cout << "Socket binded to " << hostname << ":" << service << std::endl;
    listening = true;
}

void SocketListener::listen()
{
    if (!listening)
        throw SocketException("Socket not listening");
    if (::listen(this->sock, 5) == -1)
        throw SocketException("Socket listen failed");
}

int SocketListener::accept(sockaddr_in &clientAddr)
{
    socklen_t addrsize = sizeof(clientAddr);
    int sock = ::accept(this->sock, (struct sockaddr *)&clientAddr, &addrsize);
    if (sock == -1)
        throw SocketException("Socket accept failed");
    return sock;
}

void SocketListener::close() throw()
{
    ::close(this->sock);
    this->sock = -1;
    listening = false;
}
