/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:56 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 21:56:57 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PASS.hpp"
#include "irc/Server.hpp"

PASS::PASS(Server *serv) : ACommand(serv) {}

PASS::PASS(PASS const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

PASS::~PASS() {}

int PASS::execute(Client &clicli, std::vector<std::string> args) {
    if (args.size() < 2)
        clicli << ERR_NEEDMOREPARAMS(args[0]);
    else if (_serv->getPassword().compare(args[1]))
        clicli << ERR_ALREADYREGISTRED();
    else
        clicli.setPass(args[1]);
    return 0;
}

void    PASS::descr(Client& clicli) {
    clicli << "Usage: PASS <password>\n";
}