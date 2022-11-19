/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/18 01:34:43 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PART.hpp"
#include "irc/Server.hpp"

PART::PART(Server *serv): ACommand(serv) {}

PART::PART(PART const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

PART::~PART() {}

int     PART::execute(Client &clicli, std::vector<std::string> args) {}

int     PART::secureArgs(Client &clicli, std::vector<std::string> args) {}

void    PART::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
