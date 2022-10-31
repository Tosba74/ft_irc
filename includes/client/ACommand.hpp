/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/31 01:31:51 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "client/Client.hpp"

class Server;

class ACommand {
    protected:
        Server *                _serv;
    public:

        ACommand(Server *serv);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand& operator=(ACommand const& rhs);
        
        const Server *          getServ() const;
        virtual int             execute(Client& clicli, std::vector<std::string> args) = 0;
        virtual void            descr(Client& clicli) = 0;
};

