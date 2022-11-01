/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:50:05 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 10:50:49by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/OPER.hpp"
#include "irc/Server.hpp"

OPER::OPER(Server *serv) : ACommand(serv) {}

OPER::OPER(OPER const& src) : ACommand(src) {
	if (this != &src)
		this->_serv = src._serv; 
}

OPER::~OPER() {}

	// clicli << ERR_NEEDMOREPARAMS(args[0]);
	// clicli << ERR_NOOPERHOST();
	// clicli << ERR_PASSWDMISMATCH();
	// clicli << RPL_YOUREOPER();

int		OPER::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() != 3) {
		clicli << ERR_NEEDMOREPARAMS(args[0]); 
		return 1;
	} else {
		if (_serv->getPassword().compare(args[2])) {
			clicli << ERR_PASSWDMISMATCH();
			return 1;
		}
		// pas sur du tout
		for (std::vector<int>::iterator it = _serv->getOp().begin(); it != _serv->getOp().end(); ++it) {
			if ((*it) == clicli.getSock()) {
				clicli << ERR_NOOPERHOST();
				return 1;
			}
		}
		// rien n est gere si l OPER quitte le server
	}
	_serv->setOp(clicli);
	clicli << RPL_YOUREOPER();
	return 0;
}

void	OPER::descr(Client& clicli) {
	clicli << "Usage: OPER <utilisateur> <mot de passe>\n";
}
