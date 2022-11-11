/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:33:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/11 14:03:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/USER.hpp"
#include "irc/Server.hpp"

USER::USER(Server *serv) : ACommand(serv) {}

USER::USER(USER const& src) : ACommand(src) {
	if (this != &src)
      		this->_serv = src._serv;
}

USER::~USER() {}

// TODO: verif conflit d'identite dans le server
int		USER::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 5) {
		clicli << ERR_NEEDMOREPARAMS(args[0]);
	} else if (_serv->getPassword().compare(clicli.getPass())) {
		clicli << ERR_ALREADYREGISTRED();
	} else {
		clicli.setUsername(args[1]);
		clicli.setHostname(args[2]);
		clicli.setNameserver(args[3]);
		args[4].erase(0,1);
		clicli.setRealName(args[4]);
	}
	return 0;
}

void	USER::descr(Client& clicli) {
	clicli << "Usage:: USER <nom d'utilisateur> <hôte> <nom de serveur> <nom réel>\n";
}