/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/06 17:48:55 by bmangin          ###   ########lyon.fr   */
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
    
    typedef std::vector<std::string>    args_t;
    private:
        args_t                  _arg;
        Server *                _serv;
        Client &                _client; 

    public:
        ACommand(Server *serv, Client &clicli, std::string &arg);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand&           operator=(ACommand const& rhs);
        
        const args_t &          getMsg() const;
        const Server *          getServ() const;
        const Client &          getClient() const;
};
