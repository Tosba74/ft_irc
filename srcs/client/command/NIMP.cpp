/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:05 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 19:46:00 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/NIMP.hpp"

NIMP::NIMP(Server *serv, Client &clicli, std::string msg) : ACommand(serv, clicli, msg)
{
	// this->execute();
};
NIMP::NIMP(NIMP const& src) : ACommand(src)
{
	if (this != &src)
	{
		this->_msg = src._msg;
        this->_serv = src._serv;
        this->_client = src._client;
	}
};
NIMP::~NIMP()
{
};  

int		NIMP::execute()
{
	std::cout << "Connard: " << getClient().getUsername() << std::endl;
	_client << "Connard\n";
	return 0;
};
