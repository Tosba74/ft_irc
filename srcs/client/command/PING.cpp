/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 12:54:59 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PING.hpp"
#include "irc/Server.hpp"

PING::PING(Server *serv): ACommand(serv) {}

PING::PING(PING const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

PING::~PING() {}

int PING::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() > 1 /*&& clicli.getRegister() == true*/) {
	std::string	pong = "PONG";
	for (unsigned long i = 1; i < args.size(); i++)
	{
		pong += " ";
		pong += args[i];
	}
	clicli << pong;
    }
    else
	clicli << "DEBUGG";
    return 0;
}

void    PING::descr(Client& clicli) {
    clicli << "\e[31mPING/PONG - verification que la connexion est toujours ouverte.\e[0m\n";
}
