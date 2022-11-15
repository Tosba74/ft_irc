/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/15 02:24:57 by bmangin          ###   ########lyon.fr   */
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

int     PING::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

//met les reply pour savoir lea verif a faire !
int		PING::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2 /*&& clicli.getRegister() == true*/) {
		clicli << ERR_NEEDMOREPARAMS(args[0]);
		return 1;
	} else {
		std::string	pong = "PONG";
		for (unsigned long i = 1; i < args.size(); i++)
			pong += (" " + args[i]);
		clicli << pong;
    }
    return 0;
}

void    PING::descr(Client& clicli) {
    clicli << "\e[31mPING/PONG - verification que la connexion est toujours ouverte.\e[0m\n";
}
