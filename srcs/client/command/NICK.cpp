/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/12 15:24:19 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NICK.hpp"

NICK::NICK(Server *serv) : ACommand(serv)
{

}

NICK::NICK(NICK const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

NICK::~NICK()
{
}

int NICK::unique_nick(std::string nick)
{
	for (Server::ConnectionMap::const_iterator it = _serv->begin(); it != _serv->end(); it++)
	{
	Client* curr = static_cast<Client*>(it->second);
		if (curr->getNickname() == nick)
			return (0);
	}
	return (1);
}

int NICK::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
	std::size_t len = std::distance(begin, end);
	if (len < 2)
	{
		clicli << "Usage: NICK <nickname>\n";
		return 0;
	}
	std::string nick = begin[1];
	if (unique_nick(nick))
		clicli.setNickname(nick);
	else
		clicli << ERR_NICKNAMEINUSE;
	return 0;
}