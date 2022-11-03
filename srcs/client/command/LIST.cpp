/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
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


    // clicli << ERR_NOSUCHSERVER(_serv);
    // clicli << RPL_LISTSTART();
    // clicli << RPL_LIST(args[1], "?", getChan(args[1]));
    // clicli << RPL_LISTEND();

int LIST::execute(Client &clicli, std::vector<std::string> args) {
    (void)args;
    for (std::map<std::string, Channel*>::iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); ++it) {
        clicli << it->first;
    }
    return 0;
}

void    LIST::descr(Client& clicli) {
    clicli << "\e[31mExemple\e[0m\n";
}