/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/12 15:24:04 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "client/Client.hpp"
#include "client/REPLY.hpp"

class Server;

class ACommand
{
    protected:
        Server *                _serv;
        typedef std::vector<std::string> args_t;

    public:

        ACommand(Server *serv);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand& operator=(ACommand const& rhs);
        
        const Server *          getServ() const;
        virtual int execute(Client &clicli, args_t::iterator begin, args_t::iterator end) = 0;
};

