#include "socket/SocketListen.hpp"

SocketListener::SocketListener(): listening(false)
{
}
SocketListener::~SocketListener() throw()
{
}

SocketListener::SocketListener(std::string const& hostname, std::string const& service, int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP): listening(false), Socket(type, opt, proto)
{
    bind(hostname, service);
}

void SocketListener::bind(std::string const& hostname, std::string const& service, int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP)
{
    if (listening)
        throw SocketException("Socket already listening");
    if (hostname.empty())
        throw SocketException("Hostname is empty");
    if (service.empty())
        throw SocketException("Service is empty");
    if (this->sock == -1)
        throw SocketException("Socket creation failed");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(service));
    addr.sin_addr.s_addr = inet_addr(hostname.c_str());
    if (bind(this->sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw SocketException("Socket bind failed");
    listening = true;
}

void SocketListener::listen() throw()
{
    if (!listening)
        throw SocketException("Socket not listening");
    if (listen(this->sock, 5) == -1)
        throw SocketException("Socket listen failed");
}

int SocketListener::accept(sockaddr &clientAddr)
{
    socklen_t addrsize = sizeof(clientAddr);
    int sock = ::accept(this->sock, (struct sockaddr *)&clientAddr, &addrsize);
    if (sock == -1)
        throw SocketException("Socket accept failed");
    return sock;
}

void SocketListener::close()
{
    ::close(this->sock);
    this->sock = -1;
    listening = false;
}
