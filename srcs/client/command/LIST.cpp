/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/10/31 02:32:17 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/LIST.hpp"
#include "irc/Server.hpp"

LIST::LIST(Server *serv): ACommand(serv) {}

LIST::LIST(LIST const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

LIST::~LIST() {}

int LIST::execute(Client &clicli, std::vector<std::string> args) {
    (void)args;
    for (std::map<std::string, Channel*>::iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); ++it) {
        clicli << it->first + "\n";
    }
    return 0;
}

void    LIST::descr(Client& clicli) {
    clicli << "\e[31mExemple\e[0m\n";
}