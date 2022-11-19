/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NAMES.hpp"
#include "irc/Server.hpp"

NAMES::NAMES(Server *serv): ACommand(serv) {}

NAMES::NAMES(NAMES const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

NAMES::~NAMES() {}
int NAMES::execute(Client &clicli, std::vector<std::string> args) {}

int             NAMES::secureArgs(Client &clicli, std::vector<std::string> args) {}

void    NAMES::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
