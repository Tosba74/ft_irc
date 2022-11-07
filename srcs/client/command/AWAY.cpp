/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:29:04 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/07 18:34:57 by bmangin          ###   ########lyon.fr   */
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

int AWAY::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() > 1) {
		clicli.setAway(1);
		std::string	msg;
		for (unsigned long i = 1; i < args.size(); i++)
			msg.append(" " + args[i]);
		clicli.setAwayMsg(msg);
	}
	else
		clicli.setAway(0);
	return(0);
}

void	AWAY::descr(Client& clicli) {
	clicli << "Commande: AWAY [message]\n";
}