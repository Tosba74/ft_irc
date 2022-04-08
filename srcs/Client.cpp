#include "Client.hpp"

Client::Client(int sock, int port, std::string address): port(port), server_fd(sock), address(address)
{
    client_in.sin_family = AF_INET;
    client_in.sin_port = htons(port);
    client_in.sin_addr.s_addr = inet_addr(address.c_str());
    client_in_size = sizeof(client_in);
    client_fd = accept(server_fd, (struct sockaddr *)&client_in, &client_in_size);
    if (client_fd == -1)
        throw std::runtime_error("accept() failed");
}

Client::Client(Client const &src)
{
    if (this != &src)
    {
        port = src.port;
        server_fd = src.server_fd;
        client_fd = src.client_fd;
        client_in = src.client_in;
        client_in_size = src.client_in_size;
        address = src.address;
    }
}

Client &Client::operator=(Client const &rhs)
{
    if (this != &rhs)
    {
        port = rhs.port;
        server_fd = rhs.server_fd;
        client_fd = rhs.client_fd;
        client_in = rhs.client_in;
        client_in_size = rhs.client_in_size;
        address = rhs.address;
    }
    return *this;
}

Client::~Client()
{

}

int Client::send(std::string msg)
{
    int ret = ::send(client_fd, msg.c_str(), msg.size(), 0);
    if (ret == -1)
        throw std::runtime_error("send() failed");
    return ret;
}

int Client::recv(std::string &msg)
{
    char buffer[4096];
    int ret = ::recv(client_fd, buffer, 4096, 0);
    if (ret == -1)
        throw std::runtime_error("recv() failed");
    msg = buffer;
    return ret;
}

int Client::getFd()
{
    return(client_fd);
}

std::string Client::getAddress()
{
    return (address);
}

void Client::setFd(int fd)
{
    client_fd = fd;
}

void Client::setAddress(std::string address)
{
    this->address = address;
}
