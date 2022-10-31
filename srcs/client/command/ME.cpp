/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ME.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:07:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 11:21:41 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/ME.hpp"

ME::ME(ME const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

ME::ME(Server *serv) : ACommand(serv)
{
}

ME::~ME()
{
}

int ME::execute(Client &clicli, std::vector<std::string> args)
{
	std::map<int, Client&> Clients = _channel.getClients(); // ajouter current channel
	
	std::string msg = clicli.getNickname();
	for (int i = 0; i < args.size(); i++) // determiner si 0 ou 1 selon parse
	{
		msg.append(" ");
		msg.append(args[i]);
	}
	
	for (std::map<int, Client&>::iterator it; it != Clients.end(); it++)
	{
		(*it) << msg;
	}
}
