/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:28:18 by emenella          #+#    #+#             */
/*   Updated: 2022/12/14 23:19:01 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "socket/SocketConnection.hpp"

SocketConnection::SocketConnection(int sock, sockaddr_in &addr) throw() : Socket(sock), addr(addr), addrsize(sizeof(addr)) {
    sock = fcntl(sock, F_SETFL, O_NONBLOCK);
}

SocketConnection::SocketConnection(SocketConnection const &src) throw() : Socket(src), addr(src.addr), addrsize(sizeof(src.addr)) {}

SocketConnection &SocketConnection::operator=(SocketConnection const &rhs) {
    this->addr = rhs.addr;
    this->addrsize = rhs.addrsize;
    this->writeBuffer = rhs.writeBuffer;
    this->readBuffer = rhs.readBuffer;
    this->addrsize = rhs.addrsize;
    return *this;
}

SocketConnection::~SocketConnection() {
    this->flush();
    readBuffer.clear();
    #ifdef DEBUG
        std::cout << "SocketConnection::~SocketConnection()" << std::endl;
    #endif
}

std::string SocketConnection::getAddr() {
    return inet_ntoa(this->addr.sin_addr);
}

socklen_t SocketConnection::getAddrsize() {
    return this->addrsize;
}

void SocketConnection::flush() {
    while (writeBuffer.find("\r\n") != std::string::npos)
    {
        size_t pos = writeBuffer.find("\r\n");
        if (pos != std::string::npos)
        {
            ::write(this->sock, writeBuffer.c_str(), pos);
            writeBuffer.erase(0, pos + 2);
        }
    }
}

int  SocketConnection::receive() {
    char buffer[4096];
    int  n;
    int i = -1;
    do
    {
        n = ::read(this->sock, buffer, 4096);
        buffer[n] = '\0';
        if (n > 0)
            this->readBuffer += buffer;
        i = -1;
        while(this->readBuffer[++i])
            ;
    } while (this->readBuffer[i - 1] != '\n');
    return n;
    // char buffer[4096];
    // int  n;
// 
    // n = ::read(this->sock, buffer, 4096);
    // buffer[n] = '\0';
    // if (n > 0)
        // this->readBuffer += buffer;
    // return n;
}

SocketConnection &SocketConnection::operator<<(std::string const &msg) {
    // remplacement du write/flush + protection en cas d'envoi incomplet
    // qu'est ce qui protege ??
    int b_sent = 0;
    int total_b_sent = 0;
    do {
	b_sent = send(this->getSock(), &msg[b_sent], msg.size() - total_b_sent, 0);
	total_b_sent += b_sent;
	} while (total_b_sent != (int)msg.size());
    // // je suis vraiment pas convaincu !!!

    // this->writeBuffer += msg;
    // this->writeBuffer += "\r\n";
    flush();
    return *this;
}

SocketConnection &SocketConnection::operator>>(std::string &msg) {
    receive();
    // int n_idx = this->readBuffer.find('\n',0);
    // if ((const unsigned long)n_idx == this->readBuffer.npos)
    // {
        // msg = ""; 
        // return *this;
    // }
    // msg = this->readBuffer.substr(0, n_idx);
    // this->readBuffer = this->readBuffer.substr(n_idx + 1, this->readBuffer.npos);
// 
	// std::cout << "msg = |" << msg << "|" << std::endl;
	// std::cout << "buffer = |" << this->readBuffer << "|" << std::endl;
    msg = this->readBuffer;
    this->readBuffer.clear();
    return *this;
}

bool SocketConnection::operator==(SocketConnection const &rhs) {
    return (this->getSock() == rhs.getSock());
}

int SocketConnection::getPort() {
    return ntohs(this->addr.sin_port);
}
