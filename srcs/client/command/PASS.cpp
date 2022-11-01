/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:56 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 15:34:46 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PASS.hpp"

PASS::PASS(Server *serv) : ACommand(serv) {}

PASS::PASS(PASS const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

PASS::~PASS() {}


int PASS::execute(Client &clicli, std::vector<std::string> args) {
    std::size_t len = std::distance(args.begin(), args.end());
// clicli << ERR_NEEDMOREPARAMS(args[0]);
// clicli << ERR_ALREADYREGISTRED();
    if (len < 2) {
        descr(clicli);
        // clicli << "Usage: PASSWORD <password>\n";
        return 0;
    }
    std::string pass = args[1];
    clicli.setPass(pass);
    return 0;
}

void    PASS::descr(Client& clicli) {
    clicli << "Usage: PASS <password>\n";
}