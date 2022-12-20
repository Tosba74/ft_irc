/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/12/12 13:33:58 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/KILL.hpp"
#include "irc/Server.hpp"

KILL::KILL(Server *serv): ACommand(serv) {}

KILL::KILL(KILL const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

KILL::~KILL() {}

// Réponses numériques :
    // clicli << ERR_NOPRIVILEGES() 
    // clicli << ERR_CANTKILLSERVER()
    // clicli << ERR_NEEDMOREPARAMS(args[1])
    // clicli << ERR_NOSUCHNICK(args[1]);            

int     KILL::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 3) {
        clicli << ERR_NEEDMOREPARAMS(args[0]);
        return 1;
    }
    if (!_serv->getClient(args[1])) {
        clicli << ERR_NOSUCHNICK(args[1]);
        return 1;
    }
    if (!(clicli._mod & MOD_USER_OP)) {
        clicli << ERR_NOPRIVILEGES();
        return 1;
    }
    return 0;
}

int     KILL::execute(Client &clicli, std::vector<std::string> args) {
    if (secureArgs(clicli, args))
        return 1;
    return 0;
}

void    KILL::descr(Client& clicli) {
    clicli << "Usage: KILL <pseudonyme> <commentaire>";
}
