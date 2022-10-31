/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:07:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 11:11:42 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/LIST.hpp"

LIST::LIST(LIST const& src) : ACommand(src)
{
	if (this != &src)
	{
        this->_serv = src._serv;
	}
}

LIST::LIST(Server *serv) : ACommand(serv)
{
}

LIST::~LIST()
{
}

int LIST::execute(Client &clicli, std::vector<std::string> args)
{
	//To be done
}
