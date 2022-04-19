/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:14:43 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/19 23:39:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "socket/Socket.hpp"

class SocketConnection: public Socket
{
    protected:
        struct sockaddr_in addr;
        socklen_t       addrsize;
        std::string     writeBuffer;
    public:
        pthread_t       thread;
        std::string     readBuffer;
        SocketConnection(int sock, sockaddr_in &addr) throw();
        SocketConnection(SocketConnection const &src) throw();
        SocketConnection &operator=(SocketConnection const &rhs);
        ~SocketConnection();

        std::string getAddr();
        socklen_t getAddrsize();
        int getPort();

        void flush();
        int  receive();
        int isConnected(){return this->getSock() != -1;}

        SocketConnection &operator<<(std::string const &msg);
        SocketConnection &operator>>(std::string &msg);
};