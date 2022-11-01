/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:30:04 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 17:42:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#include "irc/Channel.hpp"
#include "client/REPLY.hpp"
#include "socket/SocketConnection.hpp"

class Channel;

class Client: public SocketConnection {
    public:
        typedef std::map<std::string, Channel*>     listChannel;
    private:
        std::string                         _nickname;
        std::string                         _username;
        std::string                         _hostname;
        std::string                         _servername;
        std::string                         _version;
        std::string                         _realname;
        std::string                         _pass;
        std::string                         _mode;
        listChannel                         _channels;
        bool                                _register;
        bool                                _op;
        
    public:
        Client(int sock, sockaddr_in &addr);
        Client(Client const &src);
        Client  &operator=(Client const &rhs);
        ~Client() throw();

        void                                setNickname(std::string nickname);
        void                                setUsername(std::string username);
        void                                setHostname(std::string hostname);
        void                                setNameserver(std::string nameserver);
        void                                setVersion(std::string version);
        void                                setRealName(std::string realname);
        void                                setPass(std::string pass);
        void                                setRegister(bool register);
        void                                setOp(bool op);
        std::string                         getUsername() const;
        std::string                         getNickname() const;
        std::string                         getHostname() const;
        std::string                         getNameserver() const;
        std::string                         getVersion() const;
        std::string                         getRealName() const;
        std::string                         getPass() const;
        std::string                         getMode() const;
        std::map<std::string ,Channel*>     getChannels() const;
        bool                                getRegister() const;
        bool                                getOp() const;
        
        void                                readChannels() const;
        
        bool                                isInChannel(std::string name) const;
        void                                updateRegister();
        Client                              &operator<<(std::string const &reply);
};

std::ostream&                       operator<<(std::ostream& o, Client const& rhs);