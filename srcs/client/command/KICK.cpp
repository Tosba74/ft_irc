/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/KICK.hpp"
#include "irc/Server.hpp"

KICK::KICK(Server *serv): ACommand(serv) {}

KICK::KICK(KICK const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

KICK::~KICK() {}
int KICK::execute(Client &clicli, std::vector<std::string> args) {}

int             KICK::secureArgs(Client &clicli, std::vector<std::string> args) {}

void    KICK::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
