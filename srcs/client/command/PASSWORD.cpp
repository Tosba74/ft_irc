/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASSWORD.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:56 by emenella          #+#    #+#             */
/*   Updated: 2022/10/30 20:42:35 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PASSWORD.hpp"

PASSWORD::PASSWORD(Server *serv) : ACommand(serv) {}

PASSWORD::PASSWORD(PASSWORD const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

PASSWORD::~PASSWORD() {}

int PASSWORD::execute(Client &clicli, std::vector<std::string> args) {
    std::size_t len = std::distance(args.begin(), args.end());
    if (len < 2) {
        descr(clicli);
        // clicli << "Usage: PASSWORD <password>\n";
        return 0;
    }
    std::string pass = args[1];
    clicli.setPassword(pass);
    return 0;
}

void    PASSWORD::descr(Client& clicli) {
    clicli << "Usage: PASSWORD <password>\n";
}