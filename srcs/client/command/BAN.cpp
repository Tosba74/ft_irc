/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BAN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/BAN.hpp"
#include "irc/Server.hpp"

BAN::BAN(Server *serv): ACommand(serv) {}

BAN::BAN(BAN const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

BAN::~BAN() {}
int BAN::execute(Client &clicli, std::vector<std::string> args) {}

void    BAN::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
