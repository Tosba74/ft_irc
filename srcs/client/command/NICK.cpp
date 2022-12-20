/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/14 16:23:00 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NICK.hpp"

NICK::NICK(NICK const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

NICK::NICK(Server *serv) : ACommand(serv) {}

NICK::~NICK() {}

// clicli << ERR_NONICKNAMEGIVEN();
// clicli << ERR_ERRONEUSNICKNAME(clicli,getNickname());
// clicli << ERR_NICKNAMEINUSE(srgs[0]);
// clicli << ERR_NICKCOLLISION(srgs[0]);
	
int     NICK::secureArgs(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 2) {
		clicli << ERR_NONICKNAMEGIVEN();
		return 1;
	}
	if ((args[1].size() < 2 || args[1].size() > 9) || (args[1][0] == '&' || args[1][0] == '#')) {
		clicli << ERR_ERRONEUSNICKNAME(args[1]);
		return 1;
	}
	if (!args[1].compare(clicli.getNickname())) {
		clicli << ERR_NICKNAMEINUSE(args[1]);
		return 1;
	}
	if (_serv->getClient(args[1]) != NULL) {
		clicli << ERR_NICKCOLLISION(args[1]);
		return 1;
	}
	return 0;
}

int NICK::execute(Client &clicli, std::vector<std::string> args) {
	if (secureArgs(clicli, args))
		return 1;
	clicli.setNickname(args[1]);
	return 0;
}

void    NICK::descr(Client& clicli) {
	clicli << "Usage : NICK <pseudonyme> [ <compteur de distance> ]\n";
}
