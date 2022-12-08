/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:29:04 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/08 16:53:53 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/AWAY.hpp"

AWAY::AWAY(AWAY const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

AWAY::AWAY(Server *serv) : ACommand(serv) {}

AWAY::~AWAY() {}

int		AWAY::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

int		AWAY::execute(Client &clicli, std::vector<std::string> args) {
	std::string	msg;
	if (args.size() > 1) {
		msg = args[1];
		for (unsigned long i = 2; i < args.size(); i++)
			msg += (" " + args[i]);
		if (!(clicli._mod & MOD_AWAY))
			clicli._mod ^= MOD_AWAY;
        clicli << RPL_UNAWAY();
	} else if (args.size() == 1) {
		msg = "";
		if (clicli._mod & MOD_AWAY)
			clicli._mod ^= MOD_AWAY;
		clicli << RPL_NOWAWAY();
	}
	clicli.setAway(msg);
	return 0;
}

void	AWAY::descr(Client& clicli) {
	clicli << "Commande: AWAY [message]\n";
}
