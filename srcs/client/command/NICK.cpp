/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/24 23:45:11 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NICK.hpp"

NICK::NICK(NICK const& src) : ACommand(src) {
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

NICK::NICK(Server *serv) : ACommand(serv) {}

NICK::~NICK() {}

int NICK::execute(Client &clicli, std::vector<std::string> args) {
	std::size_t len = std::distance(args.begin(), args.end());
	if (len < 2)
	{
		clicli << "Usage: NICK <nickname>\n";
		return 0;
	}
	std::string nick = args[1];
	clicli.setNickname(nick);
	return 0;
}
