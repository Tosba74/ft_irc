/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:55 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 16:58:26 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/MODE.hpp"

MODE::MODE(Server *serv) : ACommand(serv) {}

MODE::MODE(MODE const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

MODE::~MODE() {}

// REPLY :
	// clicli << RPL_CHANNELMODEIS(args[1], clicli.getMode(), args[5]);
	// clicli << ERR_CHANOPRIVSNEEDED(args[1]);
	// clicli << RPL_BANLIST(args[1], args[5]);
	// clicli << RPL_ENDOFBANLIST(args[1]);
	// clicli << ERR_KEYSET(args[1]);
	// clicli << ERR_UNKNOWNMODE(char);
	// clicli << ERR_UMODEUNKNOWNFLAG();
	// clicli << ERR_USERSDONTMATCH();
	// clicli << RPL_UMODEIS(clicli.getMode());
	// clicli << ERR_NOSUCHCHANNEL(args[1]);
	// clicli << ERR_NOTONCHANNEL(args[1]);
	// clicli << ERR_NOSUCHNICK(args[4]);
	// clicli << ERR_NEEDMOREPARAMS(args[0]);

int		MODE::execute(Client &clicli, std::vector<std::string> args) {
	(void)clicli;
	(void)args;
	return 0;
}

void	MODE::descr(Client& clicli) {
	clicli << "Usage: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]\n";
}
