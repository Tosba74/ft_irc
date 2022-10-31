/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VERSION.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:08:32 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/31 01:17:13 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/VERSION.hpp"

VERSION::VERSION(Server *serv) : ACommand(serv) {}

VERSION::VERSION(VERSION const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

VERSION::~VERSION() {}

int		execute(Client &clicli, std::vector<std::string> args) {
	clicli.setVersion(args[2]);
	return 0;
}

void	descr(Client& clicli) {
	clicli << "VERSION [<serveur>]\n";
}