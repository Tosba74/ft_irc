/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/11/03 04:32:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NOTICE.hpp"
#include "irc/Server.hpp"

NOTICE::NOTICE(Server *serv): ACommand(serv) {}

NOTICE::NOTICE(NOTICE const& src): ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

NOTICE::~NOTICE() {}

int             NOTICE::secureArgs(Client &clicli, std::vector<std::string> args) {
    (void)args;
    (void)clicli;
    return 0;
}
int NOTICE::execute(Client &clicli, std::vector<std::string> args) {
    (void)args;
    (void)clicli;
    return 0;
}


void    NOTICE::descr(Client& clicli) {
    clicli << "Usage: NOTICE: <pseudonyme> <texte>";
}
