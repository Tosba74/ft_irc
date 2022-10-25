/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/10/25 15:22:24 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/JOIN.hpp"
#include "irc/Server.hpp"

JOIN::JOIN(Server *serv): ACommand(serv) {}

JOIN::JOIN(JOIN const& src): ACommand(src) {}

JOIN::~JOIN() {}

int JOIN::execute(Client &clicli, std::vector<std::string> args)
{
    if (clicli.getRegister() == true)
        _serv->joinChannel(args[1], clicli);
    else
        clicli << "You must be authenticated to join a channel\n";
    return 0;
}
