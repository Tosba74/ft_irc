/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/09 15:33:56 by emenella         ###   ########.fr       */
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

int NICK::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
	std::size_t len = std::distance(begin, end);
	if (len < 2)
	{
		clicli << "Usage: NICK <nickname>\n";
		return 0;
	}
	std::string nick = begin[1];
	clicli.setNickname(nick);
	return 0;
}