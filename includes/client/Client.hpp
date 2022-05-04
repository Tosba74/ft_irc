/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:30:04 by emenella          #+#    #+#             */
/*   Updated: 2022/04/28 18:38:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "irc/Channel.hpp"
#include "socket/SocketConnection.hpp"

class Channel;

class Client: public SocketConnection
{
    private:
        std::string                         _username;
        std::string                         _nickname;
        std::string                         _password;
        std::string                         _mode;
        std::map<std::string ,Channel*>     _channels;
        bool                                _register;
        bool                                _op;
        
    public:
        Client(int sock, sockaddr_in &addr);
        Client(Client const &src);
        Client  operator=(Client const &rhs);
        ~Client() throw();

        void                                setNickname(std::string nickname);
        void                                setPassword(std::string password);
        
        std::string                         getUsername() const;
        std::string                         getNickname() const;
        std::string                         getPassword() const;
        std::string                         getMode() const;
        std::map<std::string ,Channel*>     getChannels() const;
        bool                                getRegister() const;
        bool                                getOp() const;
        
        void                                readChannels() const;
        
        bool                                isInChannel(std::string name) const;
};

std::ostream&                       operator<<(std::ostream& o, Client const& rhs);