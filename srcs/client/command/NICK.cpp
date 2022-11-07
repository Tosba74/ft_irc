/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/07 18:27:25 by bmangin          ###   ########lyon.fr   */
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
	
int NICK::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 2) {
		clicli << "Usage: NICK <nickname>\n";
		return 0;
	}
	std::string nick = args[1];
	clicli.setNickname(nick);
	// jai mis sa pour pas init au debut des connection
	// if (clicli.getUsername().empty())
		// clicli.setUsername(nick);
	// if (clicli.getRealName().empty())
		// clicli.setRealName(nick);
	return 0;
}

void    NICK::descr(Client& clicli) {
	clicli << "Usage : NICK <pseudonyme> [ <compteur de distance> ]\n";
}