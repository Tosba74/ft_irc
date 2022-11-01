/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:33:27 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 15:50:07 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/USER.hpp"


USER::USER(Server *serv) : ACommand(serv) {}
		
USER::USER(USER const& src) : ACommand(src) {
	if (this != &src)
      		this->_serv = src._serv;
}

USER::~USER() {}

	// clicli << ERR_NEEDMOREPARAMS(args[0]);
	// clicli << ERR_ALREADYREGISTRED();
	
int		USER::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 4)
		clicli << ERR_NEEDMOREPARAMS(args[0]);
	clicli.setUsername(args[1]);
	clicli.setHostname(args[2]);
	clicli.setNameserver(args[3]);
	clicli.setRealName(args[4]);
	(void)clicli;
	(void)args;
	return 0;
}

void	USER::descr(Client& clicli) {
	clicli << "Usage:: USER <nom d'utilisateur> <hôte> <nom de serveur> <nom réel>\n";
}