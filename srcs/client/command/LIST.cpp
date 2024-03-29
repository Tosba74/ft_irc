/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/12/20 14:53:06 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/LIST.hpp"
#include "irc/Server.hpp"
#include <memory>

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
    if (args.size() > 2)
        clicli << ERR_NOSUCHSERVER(args[2]);
    return 0;
}

int     LIST::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    if (args.size() == 1) {
        clicli << RPL_LISTSTART();
        for (std::map<std::string, Channel*>::const_iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); it++) {
            if (!(it->second->_mod & MOD_CHAN_SECRET)) {
                if (!(it->second->_mod & MOD_USER_INVIS)) 
                    clicli << RPL_LIST(it->first, "visible", it->second->getStringUser());
                else
                    clicli << RPL_LIST(it->first, "invisible", it->second->getStringUser());
            }
        }
        clicli << RPL_LISTEND();
    } else if (args.size() == 2) {
		std::vector<std::string> tmp = splitArgs(args[1]);
		std::vector<std::string>::const_iterator it = tmp.begin();
        clicli << RPL_LISTSTART();
		for (; it != tmp.end(); ++it) {
            if (!(_serv->getChannel(*it)->_mod & MOD_USER_INVIS)) 
                clicli << RPL_LIST(*it, "visible", _serv->getChannel(*it)->getStringUser());
            else
                clicli << RPL_LIST(*it, "invisible", _serv->getChannel(*it)->getStringUser());
        }
        clicli << RPL_LISTEND();
    }
    /*
    (void)args;
    std::cout << "\e[32mChan actuel\e[0m" << clicli.getCurrchan() << std::endl;
    for (std::map<std::string, Channel*>::iterator it = _serv->_channels.begin(); it != _serv->_channels.end(); it++) {
        if (!(it->second->_mod & MOD_CHAN_SECRET))
            clicli << it->first;
        std::cout << it->first << "(" << (it->second->_mod) << ")" << std::endl;
        // std::cout << it->first << "(";
        // ft_putbytes(it->second->_mod);
        // std::cout << ")" << std::endl;
    }
    // clicli << _serv->getChannels();
    */
    return 0;
}

void    LIST::descr(Client& clicli) {
    clicli << "Usage: LIST [<canal>{,<canal>} [<serveur>]]\n";
}
