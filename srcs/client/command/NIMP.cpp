/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:05 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 13:35:08 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NIMP.hpp"

NIMP::NIMP(Server *serv) : ACommand(serv)
{

}

NIMP::NIMP(NIMP const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

NIMP::~NIMP()
{
}

int NIMP::execute(Client &clicli, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
	std::cout << "Connard: " << clicli.getUsername() << std::endl;
	clicli << "Connard\n";
	for (;begin != end; begin++)
	{
		std::cout << *begin << std::endl;
		clicli << *begin + "\n";
	}
	return 0;
}
