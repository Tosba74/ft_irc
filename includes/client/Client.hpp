/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:30:04 by emenella          #+#    #+#             */
/*   Updated: 2022/04/19 19:44:17 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc/Server.hpp"
#include "irc/Channel.hpp"
#include "socket/SocketConnection.hpp"

class Client: public SocketConnection
{
    private:
        std::string                         _username;
        std::string                         _nickname;
        std::string                         _password;
        std::map<std::string ,Channel*>     _channels;
        bool                                _register;
        bool                                _op;
        
    public:
        Client(int sock, sockaddr_in &addr);
        Client(Client const &src);
        Client  operator=(Client const &rhs);
        ~Client(;

};