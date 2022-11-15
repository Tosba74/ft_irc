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

int     OPER::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	(void)args;
	return 0;
}

int		OPER::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() != 3)
		clicli << ERR_NEEDMOREPARAMS(args[0]); 
	else if (clicli.getUsername().compare(args[1]))
		clicli << ERR_NOOPERHOST();
	else if (_serv->getPassword().compare(args[2]))
		clicli << ERR_PASSWDMISMATCH();
	else {
		_serv->setOp(clicli);
		// clicli.setOp(true);
		clicli << RPL_YOUREOPER();
	}
	std::cout << *_serv;
	return 0;
}

void	OPER::descr(Client& clicli) {
	clicli << "Usage: OPER <utilisateur> <mot de passe>\n";
}
