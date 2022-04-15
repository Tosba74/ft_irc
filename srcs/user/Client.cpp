/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:30:18 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/15 11:30:22 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "user/Client.hpp"

Client::Client(int sock): server_fd(sock)
{
    client_fd = accept(server_fd, (struct sockaddr *)&client_in, &client_in_size);
    if (client_fd == -1)
        throw std::runtime_error("accept() failed");
}

Client::Client(Client const &src)
{
    if (this != &src)
    {
        server_fd = src.server_fd;
        client_fd = src.client_fd;
        client_in = src.client_in;
        client_in_size = src.client_in_size;
    }
}

Client &Client::operator=(Client const &rhs)
{
    if (this != &rhs)
    {
        server_fd = rhs.server_fd;
        client_fd = rhs.client_fd;
        client_in = rhs.client_in;
        client_in_size = rhs.client_in_size;
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

void Client::setFd(int fd)
{
    client_fd = fd;
}