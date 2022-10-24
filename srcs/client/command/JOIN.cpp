/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/10/24 15:52:00 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/JOIN.hpp"
#include "irc/Server.hpp"

JOIN::JOIN(Server *serv): ACommand(serv) {}

JOIN::JOIN(JOIN const& src): ACommand(src) {}

JOIN::~JOIN() {}

int JOIN::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
	(void)end;
	//int ret = AuthenticationCommand::execute(clicli, begin, end);
	int ret = 1;
    if (ret == 1) {
        _serv->createChannel(begin[1]);
        _serv->joinChannel(begin[1], clicli);
    } else {
        clicli << "You must be authenticated to join a channel\n";
    }
    return 0;
}
