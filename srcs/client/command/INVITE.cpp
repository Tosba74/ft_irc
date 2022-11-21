/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/INVITE.hpp"
#include "irc/Server.hpp"

INVITE::INVITE(Server *serv): ACommand(serv) {}

INVITE::INVITE(INVITE const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

INVITE::~INVITE() {}
int     INVITE::secureArgs(Client &clicli, std::vector<std::string> args) {}
int     INVITE::execute(Client &clicli, std::vector<std::string> args) {}


void    INVITE::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
