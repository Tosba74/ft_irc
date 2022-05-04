/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 17:36:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc/Server.hpp"
#include "client/Client.hpp"

class Server;
class Client;

class InterPars
{
    public:
        virtual int         execute() PURE;
};

class ACommand: public InterPars
{
    protected:
        std::string             _msg;
        Server *                _serv;
        Client &                _client; 

    public:
        ACommand(Server *serv, Client &clicli, std::string msg);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand&           operator=(ACommand const& rhs);
        
        const std::string &     getMsg() const;
        const Server *          getServ() const;
        const Client &          getClient() const;
};
