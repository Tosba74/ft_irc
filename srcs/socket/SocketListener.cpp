/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:28:22 by emenella          #+#    #+#             */
/*   Updated: 2022/05/10 16:28:23 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket/SocketListener.hpp"

SocketListener::~SocketListener()
{
    close();
    #ifdef DEBUG
        std::cout << "SocketListener::~SocketListener()" << std::endl;
    #endif
}

SocketListener::SocketListener(int type, int opt , int proto): Socket(type, opt, proto), listening(false)
{
    fcntl(sock, F_SETFL, opt | O_NONBLOCK);
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
    socklen_t addrsize;
    int sock = ::accept(this->sock, (struct sockaddr *)&clientAddr, &addrsize);
    if (sock == -1)
        throw SocketException("Socket accept failed");
    return sock;
}

void SocketListener::close()
{
    listening = false;
}
