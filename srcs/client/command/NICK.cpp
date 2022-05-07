/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 13:44:27 by emenella         ###   ########.fr       */
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
	for (args_t::iterator it = begin; it != end; it++)
	{
		if (*it != "NICK")
		{
			clicli.setNickname(*(begin + 1));
			break;
		}
	}
	std::cout << "NICK: " << clicli.getUsername() << std::endl;
	return 0;
}