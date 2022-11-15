/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/15 00:54:01 by bmangin          ###   ########lyon.fr   */
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

int     LIST::secureArgs(Client &clicli, std::vector<std::string> args) {
    (void)clicli;
    (void)args;
    return 0;
}

int     LIST::execute(Client &clicli, std::vector<std::string> args) {
    (void)args;
    std::cout << "\e[32mChan actuel\e[0m" << clicli.getCurrchan() << std::endl;
    for (std::map<std::string, Channel*>::iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); ++it) {
        clicli << it->first;
        std::cout << it->first << "(";
        ft_putbytes(it->second->_mod);
        std::cout << ")" << std::endl;
    }
    // clicli << _serv->getChannels();
    return 0;
}

void    LIST::descr(Client& clicli) {
    clicli << "Usage: LIST [<canal>{,<canal>} [<serveur>]]\n";
}
