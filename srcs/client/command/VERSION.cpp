/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VERSION.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:08:32 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:56:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/VERSION.hpp"
#include "irc/Server.hpp"

VERSION::VERSION(Server *serv) : ACommand(serv) {}

VERSION::VERSION(VERSION const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

VERSION::~VERSION() {}

// clicli << ERR_NOSUCHSERVER(_serv);
// clicli << RPL_VERSION(_serv->getServ(), 0, _serv, "jc po du tt"");
	
int     VERSION::secureArgs(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

int		VERSION::execute(Client &clicli, std::vector<std::string> args) {
	clicli.setVersion(args[2]);
	return 0;
}

void	VERSION::descr(Client& clicli) {
	clicli << "VERSION [<serveur>]\n";
}