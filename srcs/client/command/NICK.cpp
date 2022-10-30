/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/30 20:47:25 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NICK.hpp"

NICK::NICK(NICK const& src) : ACommand(src) {
	if (this != &src) {
        this->_serv = src._serv;
	}
}

NICK::NICK(Server *serv) : ACommand(serv) {}

NICK::~NICK() {}

int NICK::execute(Client &clicli, std::vector<std::string> args) {
	std::size_t len = std::distance(args.begin(), args.end());
	if (len < 2) {
		clicli << "Usage: NICK <nickname>\n";
		return 0;
	}
	std::string nick = args[1];
	clicli.setNickname(nick);
	// jai mis sa pour pas init au debut des connection
	if (clicli.getUsername().empty())
		clicli.setUsername(nick);
	if (clicli.getRealName().empty())
		clicli.setRealName(nick);
	return 0;
}

void    NICK::descr(Client& clicli) {
	(void)clicli;
}