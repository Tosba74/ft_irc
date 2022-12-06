/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/12/06 11:51:21 by bmangin          ###   ########lyon.fr   */
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

int     PART::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }    
    return 0;
}

int     PART::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    std::vector<std::string> chans= splitArgs(args[1]);
    for (size_t i = 0; i != chans.size(); i++) {
        std::cout << "\e[33mPART " << chans[i] << "\e[0m" << std::endl;
        if (!_serv->getChannel(chans[i])) {
            clicli << ERR_NOSUCHCHANNEL(chans[i]);
            return 1;
        } else if (_serv->getChannel(chans[i])->getClients().find(clicli.getSock()) == _serv->getChannel(chans[i])->getClients().end()) {
            clicli << ERR_NOTONCHANNEL(chans[i]);
            return 1;  
        } else {
            _serv->getChannel(chans[i])->removeClient(clicli);
        }
    }
    return 0;
}


void    PART::descr(Client& clicli) {
    clicli <<  "usage: PART <canal>{,< canal >}";
}
