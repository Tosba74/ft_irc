/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:28:41 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/28 16:47:06 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define PURE = 0

class Socket
{
    protected:
        int sock;

    public:
        Socket(int sock);
        Socket(int type, int opt, int proto);
        Socket(Socket const &src);
        virtual Socket &operator=(Socket const &rhs);
        virtual ~Socket();

        class SocketException: public std::exception
        {
            private:
                std::string msg;
            public:
                SocketException(std::string const &message) throw(): msg(message) {}
                virtual ~SocketException() throw() {}
                virtual const char *what() const throw(){ return msg.c_str();}
        };
        int getSock() const;
        void setSock(int sock);
        void close();
};