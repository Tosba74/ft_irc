/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:07:06 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 15:09:33 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NICK.hpp"
#include "irc/Server.hpp"

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

void NICK::execute(Client &clicli, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
	if (begin != end)
		clicli.setUsername(*(begin + 1));
	std::cout << "NICK: " << clicli.getUsername() << std::endl;	
}