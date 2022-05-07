/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/06 19:31:41 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc/Server.hpp"
#include "client/Client.hpp"

class Server;
class Client;


class ACommand
{

    protected:
        typedef std::vector<std::string> args_t;
        Server *                _serv;

    public:
        ACommand(Server *serv);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand& operator=(ACommand const& rhs);
        
        const Server *          getServ() const;
        virtual int execute(Client &clicli, args_t::iterator begin, args_t::iterator end) = 0;
};

