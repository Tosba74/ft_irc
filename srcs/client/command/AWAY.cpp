/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:07:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 11:09:16 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/AWAY.hpp"

AWAY::AWAY(AWAY const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

AWAY::AWAY(Server *serv) : ACommand(serv)
{
}

AWAY::~AWAY()
{
}

int AWAY::execute(Client &clicli, std::vector<std::string> args)
{
	if (args.size() > 1) //si on recoit la commande en args[0], sinon > 0
	{
		clicli.setAway(1);
		std::string	msg;
		for (int i = 0; i < args.size(); i++)
		{
			msg.append(" ");
			msg.append(args[i]);
		}
		clicli.setAwayMsg(msg);
	}
	else
		clicli.setAway(0);
	return(0);
}
