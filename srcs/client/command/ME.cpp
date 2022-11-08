/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ME.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:23:14 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/08 10:47:10 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/ME.hpp"
#include "irc/Server.hpp"

ME::ME(Server *serv) : ACommand(serv) {}

ME::ME(ME const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

ME::~ME() {}

int ME::execute(Client &clicli, std::vector<std::string> args) {
	/*
	std::map<int, Client&> Clients = _channels.getClients(); // ajouter current channel

	std::string msg = clicli.getNickname();
	for (unsigned long i = 1; i < args.size(); i++)
		msg.append(" " + args[i]);
	for (std::map<int, Client&>::const_iterator it = _serv->_channels.getClients().begin(); it != _serv->_channels.getClients().end(); ++it)
		(*it).second << msg;
	*/
	Channel*	curr = _serv->getChannel(clicli.getCurrchan());
	std::string msg = clicli.getNickname();

	for (unsigned long i = 1; i < args.size(); ++i)
		msg.append(" " + args[i]);
	std::cout << "\e[32m" << msg << "\e[0m" << std::endl;
	for (std::map<int, Client&>::const_iterator it = curr->getClients().begin(); it != curr->getClients().end(); ++it)
		(*it).second << msg;
	// curr << msg;
	return 0;
}

void	ME::descr(Client& clicli) {
	(void)clicli;
}
