/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/17 19:37:08 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/KILL.hpp"
#include "irc/Server.hpp"

// Réponses numériques :
    // clicli << ERR_NOPRIVILEGES() 
    // clicli << ERR_CANTKILLSERVER()
    // clicli << ERR_NEEDMOREPARAMS(args[1])
    // clicli << ERR_NOSUCHNICK(args[1]);            

KILL::KILL(Server *serv): ACommand(serv) {}

KILL::KILL(KILL const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

KILL::~KILL() {}
int     KILL::execute(Client &clicli, std::vector<std::string> args) {}

int     KILL::secureArgs(Client &clicli, std::vector<std::string> args) {}

void    KILL::descr(Client& clicli) {
    clicli << e[31mExemplee[0mn;
}
