/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSG.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:07:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/30 20:28:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/MSG.hpp"

MSG::MSG(MSG const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

MSG::MSG(Server *serv) : ACommand(serv)
{
}

MSG::~MSG()
{
}

int MSG::execute(Client &clicli, std::vector<std::string> args)
{
	for (std::map<std::string, Client*>::iterator it = _serv.clientAll.begin(); it != _serv.clientAll.end(); ++it)
	{
		if ((((*it).second)->getNickname()).compare(args[0]) == 0)
		{
			Client	*Target = getTarget(args[0]);
			std::string message = "PRIVMSG ";
			message.join(args[0] + " :" + args[1]);
			// Target << message;
			send(Target.sock, message.c_str(), message.length(), 0)
		}
	}
}

Client	*getTarget(std::string name)
{
	for (std::map<std::string, Client*>::iterator it = _serv.clientAll.begin(); it != _serv.clientAll.end(); ++it)
        {
                if ((((*it).second)->getNickname()).compare(name) == 0)
       			return (*it);
       	}
	return (nullptr);
}
